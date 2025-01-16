#include "led_pendulum.h"
#include "inc/tm4c1294ncpdt.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"

void Pendulum_Init(void) {
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOL);  // Enable Port L
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOL));

    GPIOPinTypeGPIOOutput(GPIO_PORTL_BASE, 0xFF);  // Configure all Port L pins as output
}

void Pendulum_DisplayDistance(uint32_t distance) {
    // Scale distance to LED range (example: 3-300 cm to LED 0-7)
    uint8_t ledIndex = (distance <= 300) ? (distance / 40) : 0;
    GPIOPinWrite(GPIO_PORTL_BASE, 0xFF, (1 << ledIndex));  // Light up corresponding LED
}
