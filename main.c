/*
 * PulsGenerator.c
 *
 *  Created on: 30.01.2020
 *      Author: Pawel Buczek
 */

// FreeRTOS headers
#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h>
#include <queue.h>

// Standard and Tiva hardware libraries
#include <inc/tm4c1294ncpdt.h>  // board parameterization
#include <stdint.h>
#include <stdbool.h>
#include <string.h> // for strcmp
#include <inc/hw_memmap.h>
#include <inc/hw_gpio.h>
#include <driverlib/gpio.h>
#include <driverlib/sysctl.h>
#include <examples/boards/ek-tm4c1294xl/drivers/pinout.h> // for PinoutSet
#include <math.h>

// ISR setup of the project
#include "isr.h"

// Structure containing parameters passed to TaskPeriodic function
struct adcTaskParams_ {
    unsigned int pin_;                          // output pin
    unsigned int port_;                         // output port
    unsigned int defaultHalfFlashDuration_;     // duration of the half-period
    TickType_t taskExecutionPeriod_;            // task delay after pulse series
    unsigned int flashCount_;                   // number of pulses in the pulse series
    xSemaphoreHandle moduleMutex_;              // mutex handle
    QueueHandle_t halfFlashDurationQueue_;      // queue handle
};

struct buttonServiceTaskParams_ {
    unsigned int pin_;                          // pin connected to the button
    unsigned int port_;                         // port of the button
    unsigned int modifiedHalfFlashDuration_;    // duration of modified pulse, will be placed in a queue
    QueueHandle_t halfFlashDurationQueue_;      // FreeRTOS queue handle
};

struct adcTaskParams_ adcTP0_, adcTP1_;         // instances of the structure
struct buttonServiceTaskParams_ buttonServiceTP_;    // instance of the structure

// Task functions for the pulse generator functionality
static void adcTask_(void * taskParameters);
static void buttonServiceTask_(void * taskParameters);

// Task functions for teaching purposes
unsigned int activationCounterJ1_ = 0;
static void dataProcessingTask_(void * taskParameters);

// Auxiliary functions
static void hardwareSetup_(void);
static void defaultApplicationErrorHandler_(void);

// Fake data to process
volatile double xdat, ydat;
unsigned int const iterCout = 1000000;

// Task priorities
UBaseType_t const adcTaskHighPriority_        = 1;
UBaseType_t const adcTaskLowPriority_         = 1;
UBaseType_t const buttonServiceTaskPriority_  = 1;
UBaseType_t const dataProcessingTaskPriority_ = 2;
// The idle task has the lowest priority with numerical value of 0

void main(void) {
    // Queue for passing information about the length of a pulse to the low priority periodic task.
    // The queue is populated by the buttonServiceTask (periodically polling button 0) and the interrupt service routine checking the state of button 1.
    // The queue can hold up to 20 period change requests.
    QueueHandle_t halfFlashDurationQueue = xQueueCreate(20, sizeof(unsigned int));
    if (halfFlashDurationQueue == NULL) {
        // Handle error
        defaultApplicationErrorHandler_();
    }

    // Creating mutex, it is a special case of a (binary) semaphore
    SemaphoreHandle_t moduleMutex = xSemaphoreCreateMutex();
    if (moduleMutex == NULL) {
        // Handle error
        defaultApplicationErrorHandler_();
    }

    // Configuration of the adcTaskHigh
    adcTP0_.port_ = GPIO_PORTN_BASE;
    adcTP0_.pin_ = GPIO_PIN_0;
    adcTP0_.defaultHalfFlashDuration_ = 500;  // Duration for high priority task
    adcTP0_.taskExecutionPeriod_ = pdMS_TO_TICKS(10000);  // 10 seconds
    adcTP0_.flashCount_ = 5;
    adcTP0_.moduleMutex_ = moduleMutex;
    adcTP0_.halfFlashDurationQueue_ = halfFlashDurationQueue;
    xTaskCreate(adcTask_, "adcTaskHigh", 200, &adcTP0_, adcTaskHighPriority_, NULL);

    // Configuration of the low priority periodic task
    adcTP1_.port_ = GPIO_PORTF_BASE;
    adcTP1_.pin_ = GPIO_PIN_0;
    adcTP1_.defaultHalfFlashDuration_ = 300;  // Default duration
    adcTP1_.taskExecutionPeriod_ = pdMS_TO_TICKS(0);  // Always when given CPU
    adcTP1_.flashCount_ = 1;
    adcTP1_.moduleMutex_ = moduleMutex;
    adcTP1_.halfFlashDurationQueue_ = halfFlashDurationQueue;
    xTaskCreate(adcTask_, "adcTaskLow", 200, &adcTP1_, adcTaskLowPriority_, NULL);

    // Creating switch task checking the state of the button at pin 0
    buttonServiceTP_.port_ = GPIO_PORTJ_BASE;
    buttonServiceTP_.pin_ = GPIO_PIN_0;
    buttonServiceTP_.modifiedHalfFlashDuration_ = 110;
    buttonServiceTP_.halfFlashDurationQueue_ = halfFlashDurationQueue;
    xTaskCreate(buttonServiceTask_, "buttonServiceTask", 200, &buttonServiceTP_, buttonServiceTaskPriority_, NULL);

    // Configuration of an event driven task
    // It is given the highest priority, as it should react as soon as possible to the event.
    // The handle to this task is necessary, as it will be passed to the ISR configuration.
    TaskHandle_t eventDrivenTask = NULL;
    xTaskCreate(dataProcessingTask_, "dataProcessingTask", 200, NULL, dataProcessingTaskPriority_, &eventDrivenTask);

    // Perform ISR initialization
    unsigned int modifiedHalfFlashDurationIsr = 60;
    configureISR(halfFlashDurationQueue, eventDrivenTask, modifiedHalfFlashDurationIsr);

    // Perform hardware initialization. It is deferred up to this point because it activates interrupts.
    hardwareSetup_();

    // Start FreeRTOS scheduler
    vTaskStartScheduler();

    // This statement should never be reached
    defaultApplicationErrorHandler_();
}

/**
 * The two periodic tasks "adcTaskHigh" and "adcTaskLow" are based on this function.
 */
static void adcTask_(void * taskParameters) {
    // Parameter variable cast
    struct adcTaskParams_ const * const taskParametersCast = (struct adcTaskParams_ *)taskParameters;
    const unsigned int pin = taskParametersCast->pin_;
    const unsigned int port = taskParametersCast->port_;
    TickType_t taskExecutionPeriod = taskParametersCast->taskExecutionPeriod_;
    const unsigned int halfFlashDurationFundamental = taskParametersCast->defaultHalfFlashDuration_;
    const unsigned int flashCount_ = taskParametersCast->flashCount_;
    xSemaphoreHandle const mutex = taskParametersCast->moduleMutex_;
    QueueHandle_t const halfFlashDurationQueue = taskParametersCast->halfFlashDurationQueue_;

    int halfFlashDuration;  // Flash half period
    int halfFlashDurationModified;  // Variable for storing the queue message
    char const * const TaskName = pcTaskGetName(NULL);  // Task name
    unsigned int flashCounter;  // Pulse counter

    // Variable used by vTaskDelayUntil()
    TickType_t lastExecutionTime = xTaskGetTickCount();

    // Fundamental, infinite task loop
    while(1) {
        // Request the mutex. The mutex controls the access to the GPIO peripherals.
        // A block time is specified, so the calling task will be placed in the Blocked state to wait for the mutex to be available.
        // Infinite block time is used (portMAX_DELAY), so it is not necessary to check the value returned as
        // xSemaphoreTake will only return when data is available.
        xSemaphoreTake(mutex, portMAX_DELAY);

        // Default duration of flash half-period
        halfFlashDuration = halfFlashDurationFundamental;

        // Only low priority task can have its flash rate changed
        if (0 == strcmp("adcTaskLow", TaskName) && halfFlashDurationQueue) {
            // Obtain a message from the queue halfFlashDurationQueue_. Do not block if the queue is empty, block time is 0.
            __attribute__((unused))
            UBaseType_t itemCount;  // Count of elements in the queue, for debugging
            itemCount = uxQueueMessagesWaiting(halfFlashDurationQueue);

            // If an element was extracted from the queue, modify the halfFlashDuration
            if (pdTRUE == xQueueReceive(halfFlashDurationQueue, &halfFlashDurationModified, 0)) {
                // The message from the queue determines the flash rate
                halfFlashDuration = halfFlashDurationModified;
            }
        }

        // Generate the series of flashes
        for (flashCounter = 0; flashCounter < flashCount_; ++flashCounter) {
            GPIOPinWrite(port, pin, 1);  // Set pin high

            // Delay the task. During this time other tasks, which do not require the mutex, can run.
            vTaskDelay(halfFlashDuration);

            GPIOPinWrite(port, pin, 0);  // Set pin low
            vTaskDelay(halfFlashDuration);  // Delay the task
        }

        // Release the mutex
        xSemaphoreGive(mutex);

        // Delay the task such that it wakes up every taskExecutionPeriod
        vTaskDelayUntil(&lastExecutionTime, taskExecutionPeriod);
    }
}

/**
 * The function periodically checks the state of a pin connected to a button.
 * If it detects the button pressed it puts an item (modified period) into the queue.
 * Note: pressing the key sets the corresponding GPIO pin to low.
 */
static void buttonServiceTask_(void * taskParameters) {
    // Parameter variable cast
    struct buttonServiceTaskParams_ const * const taskParametersCast = (struct buttonServiceTaskParams_ *)taskParameters;
    const unsigned int pin = taskParametersCast->pin_;
    const unsigned int port = taskParametersCast->port_;
    const unsigned int queueItem = taskParametersCast->modifiedHalfFlashDuration_;
    QueueHandle_t switchQueue = taskParametersCast->halfFlashDurationQueue_;

    // Polling but no busy-wait
    while(1) {
        // Check the state of the button and put the item in the queue if detected pressed
        if (GPIOPinRead(port, pin) == 0) {  // Button pressed (active low)
            xQueueSend(switchQueue, &queueItem, 0);
        }
        vTaskDelay(pdMS_TO_TICKS(100UL));  // Delay the task
    }
}

/**
 * Event driven task which is waken up by an event.
 * It gets notifies from an interrupt service routine.
 */
static void dataProcessingTask_(void * taskParameters) {
    // Number of events to process
    uint32_t eventsToProcessCount;

    while(1) {
        // The task is waiting indefinitely for a notification (portMAX_DELAY) and clears all the notifications upon running (pdTRUE).
        eventsToProcessCount = ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        // Process all the events
        while(eventsToProcessCount > 0) {
            // Count the button pressing events
            ++activationCounterJ1_;
            eventsToProcessCount--;

            // Measure time delay
            TickType_t executionBeginTime = xTaskGetTickCount();

            // Some fake calculations -------------------------------This leads to long delay when J1 is pressed!
//            unsigned int i;
//            for (i = 0; i < iterCout; ++i) {
//                ydat = cos(xdat);
//            }

            // Compute time delay
            TickType_t executionEndTime = xTaskGetTickCount();
            __attribute__((unused))
            TickType_t executionTime = executionEndTime - executionBeginTime;
            asm(" nop");
        }
    }
}

/**
 * Hardware setup function
 */
static void hardwareSetup_(void) {
    // Set CPU frequency to 120 MHz. Note that this number must correspond to the setup in os/FreeRTOSConfig.h
    SysCtlClockFreqSet(SYSCTL_XTAL_25MHZ | SYSCTL_OSC_MAIN | SYSCTL_USE_PLL | SYSCTL_CFG_VCO_480, 120000000);

    // Enable necessary GPIO ports
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOJ);

    // Pins will be used as GPIOs
    PinoutSet(false, false);

    // Wait for the modules to activate
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF));
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPION));
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOJ));

    // In/out setup
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_0);
    GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_0);
    GPIOPinTypeGPIOInput(GPIO_PORTJ_AHB_BASE, GPIO_PIN_1 | GPIO_PIN_0);

    // Use pull-up resistor, if the button is not pressed is gives high (1) on the GPIO
    GPIO_PORTJ_AHB_PUR_R = GPIO_PIN_1 | GPIO_PIN_0;

    // Pin J0 (left button) is sensed by the buttonServiceTask using polling.
    // Driving pin J1 (right button) should cause an interrupt, configured below.
    // Configure interrupt for pin J1
    GPIO_PORTJ_AHB_IS_R  &= ~0x02;  // Sense "edge-sensitive"
    GPIO_PORTJ_AHB_IBE_R &= ~0x02;  // Trigger set to "single edge"
    GPIO_PORTJ_AHB_IEV_R &= ~0x02;  // Interrupt event to falling edge (upon pressing)
    GPIO_PORTJ_AHB_ICR_R |=  0x02;  // Clear the interrupt bit
    GPIO_PORTJ_AHB_IM_R  |=  0x02;  // Unmask
    NVIC_EN1_R |= (1 << 0x13);      // Enable PortJ interrupt (Int#33/Vec#20) in NVIC
}

/**
 * Default application error handler
 */
static void defaultApplicationErrorHandler_(void) {
    while(1) {
        asm(" nop");
    }
}
