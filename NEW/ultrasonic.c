#include "ultrasonic.h"
#include "inc/tm4c1294ncpdt.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/timer.h"
#include "driverlib/interrupt.h"

#define TRIGGER_PORT GPIO_PORTM_BASE
#define TRIGGER_PIN GPIO_PIN_1
#define ECHO_PORT GPIO_PORTM_BASE
#define ECHO_PIN GPIO_PIN_2

static volatile uint32_t distance = 0;
static volatile uint32_t startTime = 0;

void Ultrasonic_Init(void) {
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOM);  // Enable Port M
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOM));

    GPIOPinTypeGPIOOutput(TRIGGER_PORT, TRIGGER_PIN);  // Trigger as output
    GPIOPinTypeGPIOInput(ECHO_PORT, ECHO_PIN);         // Echo as input

    GPIOIntDisable(ECHO_PORT, ECHO_PIN);
    GPIOIntClear(ECHO_PORT, ECHO_PIN);
    GPIOIntTypeSet(ECHO_PORT, ECHO_PIN, GPIO_BOTH_EDGES);  // Rising and falling edge
    GPIOIntEnable(ECHO_PORT, ECHO_PIN);
    IntEnable(INT_GPIOM);  // Enable interrupt in NVIC
}

void Ultrasonic_Trigger(void) {
    GPIOPinWrite(TRIGGER_PORT, TRIGGER_PIN, TRIGGER_PIN);
    SysCtlDelay(SysCtlClockGet() / 3000000);  // 10 µs delay
    GPIOPinWrite(TRIGGER_PORT, TRIGGER_PIN, 0);
}

uint32_t Ultrasonic_GetDistance(void) {
    return distance;
}

void EchoISR(void) {
    GPIOIntClear(ECHO_PORT, ECHO_PIN);

    if (GPIOPinRead(ECHO_PORT, ECHO_PIN)) {
        // Rising edge: start timing
        startTime = TimerValueGet(TIMER0_BASE, TIMER_A);
    } else {
        // Falling edge: stop timing and calculate distance
        uint32_t endTime = TimerValueGet(TIMER0_BASE, TIMER_A);
        uint32_t pulseWidth = (startTime > endTime) ? (startTime - endTime) : (0xFFFF - endTime + startTime);
        distance = (pulseWidth * 0.0343) / 2;  // Convert to cm
    }
}
