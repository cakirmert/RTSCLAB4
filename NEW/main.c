#include <stdint.h>
#include "ultrasonic.h"
#include "led_pendulum.h"
#include "inc/tm4c1294ncpdt.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"
#include "driverlib/interrupt.h"

// Timer ISR for periodic measurement
void TimerISR(void) {
    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    Ultrasonic_Trigger();
}

int main(void) {
    // Initialize modules
    Ultrasonic_Init();
    Pendulum_Init();

    // Configure Timer for periodic measurement
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);
    TimerLoadSet(TIMER0_BASE, TIMER_A, SysCtlClockGet() / 50);  // 20 ms
    IntEnable(INT_TIMER0A);
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    TimerEnable(TIMER0_BASE, TIMER_A);

    IntMasterEnable();  // Enable global interrupts

    while (1) {
        uint32_t distance = Ultrasonic_GetDistance();
        Pendulum_DisplayDistance(distance);  // Display distance dynamically
    }
}
