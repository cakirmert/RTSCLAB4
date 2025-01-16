#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include <stdint.h>
#include <stdbool.h>

// Initialize ultrasonic module
void Ultrasonic_Init(void);

// Trigger a new distance measurement
void Ultrasonic_Trigger(void);

// Get the last measured distance
uint32_t Ultrasonic_GetDistance(void);

#endif // ULTRASONIC_H
