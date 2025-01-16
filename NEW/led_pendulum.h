#ifndef LED_PENDULUM_H
#define LED_PENDULUM_H

#include <stdint.h>

// Initialize LED pendulum
void Pendulum_Init(void);

// Display distance on the LED pendulum
void Pendulum_DisplayDistance(uint32_t distance);

#endif // LED_PENDULUM_H
