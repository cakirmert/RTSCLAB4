/*
 * isr.c
 *
 *  Created on: 30.01.2020
 *      Author: pbuczek
 */

#include <stdint.h>
#include <inc/tm4c1294ncpdt.h>  // board parameterization

// FreeRTOS kernel
#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>
#include <driverlib/gpio.h>
#include <stdbool.h>

// Project-specific interrupt service routines (ISR)
#include "isr.h"

// Static variables to hold the queue, task handle, and modified flash duration
static QueueHandle_t switchQueue_;
static TaskHandle_t eventDrivenTask_;
static unsigned int modifiedHalfFlashDurationIsr_;

/**
 * @brief Configure the ISR with the queue, task handle, and modified flash duration.
 *
 * @param switchQueue The queue handle for passing data from ISR to tasks.
 * @param eventDrivenTask The handle of the task to be notified.
 * @param modifiedHalfFlashDurationIsr The modified flash duration to be sent to the queue.
 */
void configureISR(QueueHandle_t switchQueue, TaskHandle_t eventDrivenTask, unsigned int modifiedHalfFlashDurationIsr) {
    switchQueue_ = switchQueue;
    eventDrivenTask_ = eventDrivenTask;
    modifiedHalfFlashDurationIsr_ = modifiedHalfFlashDurationIsr;
}

/**
 * @brief ISR for GPIO Port J. Handles button press interrupts.
 */
void gpioPortJIsr(void) {
    // Save the interrupt source
    uint32_t mis = GPIO_PORTJ_AHB_MIS_R;

    // Clear the interrupt bits
    GPIO_PORTJ_AHB_ICR_R = mis;

    // The xHigherPriorityTaskWoken parameter must be initialized to pdFALSE as
    // it will get set to pdTRUE inside the interrupt-safe API function if a
    // context switch is required.
    BaseType_t xHigherPriorityTaskWoken0 = pdFALSE;
    BaseType_t xHigherPriorityTaskWoken1 = pdFALSE;

    // Check if the button at pin 1 generated the interrupt
    if (mis & GPIO_PIN_1) {
        // Add element modifiedHalfFlashDurationIsr_ to the queue switchQueue_
        xQueueSendFromISR(switchQueue_, &modifiedHalfFlashDurationIsr_, &xHigherPriorityTaskWoken0);

        // Notify (wake up) the event processing task (eventDrivenTask_)
        vTaskNotifyGiveFromISR(eventDrivenTask_, &xHigherPriorityTaskWoken1);
    }

    // Pass the xHigherPriorityTaskWoken value into portYIELD_FROM_ISR().
    // If xHigherPriorityTaskWoken was set to pdTRUE inside vTaskNotifyGiveFromISR()
    // then calling portYIELD_FROM_ISR() will request a context switch.
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken0 || xHigherPriorityTaskWoken1);
}
