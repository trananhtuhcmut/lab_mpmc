/*
 * scheduler.h
 *
 *  Created on: Nov 1, 2026
 *      Author: trananhtu
 */
#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

#include <stdint.h>

typedef struct {
    void (*pTask)(void);      // Pointer function
    uint32_t Delay;           // Delta delay
    uint32_t Period;          // 0 mean once only
    uint8_t RunMe;            // Flag
    uint32_t TaskID;          // Task ID
} sTask;

#define SCH_MAX_TASKS 10      // Max task

void SCH_Init(void);
void SCH_Update(void);
void SCH_Dispatch_Tasks(void);
uint32_t SCH_Add_Task(void (*pFunction)(), uint32_t DELAY, uint32_t PERIOD);
uint8_t SCH_Delete_Task(uint32_t taskID);

#endif /* INC_SCHEDULER_H_ */



