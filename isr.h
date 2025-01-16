/*
 * isr.h
 *
 *  Created on: 30.01.2020
 *      Author: pbuczek
 */

#ifndef MAIN_ISR_H_
#define MAIN_ISR_H_

// FreeRTOS kernel
#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>

/**
 * @brief Configure the ISR with the queue, task handle, and modified flash duration.
 *
 * @param switchQueue The queue handle for passing data from ISR to tasks.
 * @param eventDrivenTask The handle of the task to be notified.
 * @param modifiedHalfFlashDurationIsr The modified flash duration to be sent to the queue.
 */
void configureISR(QueueHandle_t switchQueue, TaskHandle_t eventDrivenTask, unsigned int modifiedHalfFlashDurationIsr);

/**
 * @brief ISR for GPIO Port J. Handles button press interrupts.
 */
void gpioPortJIsr(void);

#endif /* MAIN_ISR_H_ */
