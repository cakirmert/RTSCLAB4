/*
 * FreeRTOSConfig.h
 *
 *  Created on: 30.01.2020
 *      Author: Pawel Buczek
 *
 */

#ifndef OS_FREERTOSCONFIG_H_
#define OS_FREERTOSCONFIG_H_

/* Per-Project FreeRTOS Configuration */

/*
 * Check all the required application specific macros have been defined.
 * These macros are application specific and (as downloaded) are defined
 * within FreeRTOSConfig.h.
 */

#define configMINIMAL_STACK_SIZE                128         // idle task stack (in 32-bit words)
#define configMAX_PRIORITIES                    8
#define configUSE_PREEMPTION                    1
#define configUSE_IDLE_HOOK                     0
#define configUSE_TICK_HOOK                     0
#define INCLUDE_vTaskPrioritySet                0
#define INCLUDE_uxTaskPriorityGet               0
#define INCLUDE_vTaskDelete                     0
#define INCLUDE_vTaskSuspend                    1
#define INCLUDE_vTaskDelay                      1           // necessary for delaying tasks
#define INCLUDE_vTaskDelayUntil                 1           // for the "delay until" functionality
#define configUSE_16_BIT_TICKS                  0
#define configKERNEL_INTERRUPT_PRIORITY         (7 << 5)
#define configMAX_SYSCALL_INTERRUPT_PRIORITY    (1 << 5)
#define configTOTAL_HEAP_SIZE                   (8 * 1024)
#define configCPU_CLOCK_HZ                      120000000UL // 120MHz clock
#define configTICK_RATE_HZ                      1000        // tick interrupt every 1ms

// additional options
#define configUSE_MUTEXES                       1           // mutex required
#define INCLUDE_pcTaskGetName                   1           // access to the task name

#endif /* OS_FREERTOSCONFIG_H_ */
