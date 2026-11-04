/*
 * scheduler.c
 *
 *  Created on: Nov 1, 2026
 *      Author: trananhtu
 */


#include "scheduler.h"

static sTask SCH_tasks_G[SCH_MAX_TASKS];
static uint32_t nextTaskID = 1;
extern volatile uint32_t system_time_ms;
extern volatile uint32_t snapshot_time_ms;

//Clean for initial
void SCH_Init(void) {
    for (int i = 0; i < SCH_MAX_TASKS; i++) {
        SCH_tasks_G[i].pTask = 0;
        SCH_tasks_G[i].Delay = 0;
        SCH_tasks_G[i].Period = 0;
        SCH_tasks_G[i].RunMe = 0;
        SCH_tasks_G[i].TaskID = 0;
    }
}




// Add Task
uint32_t SCH_Add_Task(void (*pFunction)(), uint32_t DELAY, uint32_t PERIOD) {
    int index = -1;
    // To the nearet unoccupied slot
    for (int i = 0; i < SCH_MAX_TASKS; i++) {
        if (SCH_tasks_G[i].pTask == 0) {
            index = i;
            break;
        }
    }
    if (index == -1) return 0; // No empty


    // Find insert position
        uint32_t accumulative_delay = 0;
        uint32_t prev_accumulative = 0;
        int insert_pos = -1;

        for (int i = 0; i < SCH_MAX_TASKS; i++) {
            if (SCH_tasks_G[i].pTask != 0) {
            	prev_accumulative = accumulative_delay;
                accumulative_delay += SCH_tasks_G[i].Delay; //Addition previous tu find poss
                if (DELAY < accumulative_delay) {
                    insert_pos = i;
                    break;
                }
            }
        }

    // Found at middle or at head
        if (insert_pos != -1) {
            // +1 position
            for (int i = SCH_MAX_TASKS - 1; i > insert_pos; i--) {
                SCH_tasks_G[i] = SCH_tasks_G[i - 1];
            }

            // At head
            // 1= 10s, 2=20s (30s delay), insert 4 -> 1 = 4s, 2= 10-4=6s, 3 remain
            	SCH_tasks_G[insert_pos].pTask = pFunction;
            	SCH_tasks_G[insert_pos].Delay = DELAY - prev_accumulative;
            	SCH_tasks_G[insert_pos].Period = PERIOD;
            	SCH_tasks_G[insert_pos].RunMe = (SCH_tasks_G[insert_pos].Delay == 0 && insert_pos == 0) ? 1 : 0;
            	SCH_tasks_G[insert_pos].TaskID = nextTaskID++;


                // Next task = next task - delay (6s)
            	SCH_tasks_G[insert_pos + 1].Delay -= SCH_tasks_G[insert_pos].Delay;
            	        if (insert_pos == 0) {
            	            SCH_tasks_G[insert_pos + 1].RunMe = 0;
            	        }

            	        return SCH_tasks_G[insert_pos].TaskID;
        }

                SCH_tasks_G[index].pTask = pFunction;
                SCH_tasks_G[index].Delay = DELAY - accumulative_delay;
                SCH_tasks_G[index].Period = PERIOD;
                SCH_tasks_G[index].RunMe = 0;
                SCH_tasks_G[index].TaskID = nextTaskID++;
                return SCH_tasks_G[index].TaskID;
}



void SCH_Update(void) {
    if (SCH_tasks_G[0].pTask != 0) { // Check if has task
        if (SCH_tasks_G[0].Delay > 0) {
            SCH_tasks_G[0].Delay--;
        }

        // Count down, start run
        if (SCH_tasks_G[0].Delay == 0) {
            SCH_tasks_G[0].RunMe += 1;
        }
    }
}




void SCH_Dispatch_Tasks(void) {
	if (SCH_tasks_G[0].pTask != 0 && (SCH_tasks_G[0].RunMe > 0 || SCH_tasks_G[0].Delay == 0)) {
	   snapshot_time_ms = system_time_ms; // Capture time

	   void (*due_tasks[SCH_MAX_TASKS])(void); //Temp task array
	   int count = 0;


    // Find task flagged (or delay has come)
    while (SCH_tasks_G[0].pTask != 0 && (SCH_tasks_G[0].RunMe > 0 || SCH_tasks_G[0].Delay == 0)) {
        void (*pFunc)() = SCH_tasks_G[0].pTask;
        uint32_t period = SCH_tasks_G[0].Period;
        uint32_t taskID = SCH_tasks_G[0].TaskID;

        // Delete the dispatched task (1st element)
        SCH_Delete_Task(taskID);

        // Periodic task
        if (period > 0) {
            SCH_Add_Task(pFunc, period, period);
        }

        due_tasks[count++] = pFunc;
            }
    	//Run
            for (int i = 0; i < count; i++) {
                (*due_tasks[i])();
            }
}
}


uint8_t SCH_Delete_Task(uint32_t taskID) {
	if (taskID == 0) return 0;
    int delete_index = -1;
    // Find task ID
    for (int i = 0; i < SCH_MAX_TASKS; i++) {
            if (SCH_tasks_G[i].pTask != 0 && SCH_tasks_G[i].TaskID == taskID) {
                delete_index = i;
                break;
            }
        }

    // Not found -> Error = 0
    if (delete_index == -1) return 0;

    // Not final task
    if (delete_index < SCH_MAX_TASKS - 1 && SCH_tasks_G[delete_index + 1].pTask != 0) {
        SCH_tasks_G[delete_index + 1].Delay += SCH_tasks_G[delete_index].Delay; //Add delay to the next one deleted
    }

    // Shift left
    for (int i = delete_index; i < SCH_MAX_TASKS - 1; i++) {
        SCH_tasks_G[i] = SCH_tasks_G[i + 1];
    }

    // Delete final one
    SCH_tasks_G[SCH_MAX_TASKS - 1].pTask = 0;
    SCH_tasks_G[SCH_MAX_TASKS - 1].Delay = 0;
    SCH_tasks_G[SCH_MAX_TASKS - 1].Period = 0;
    SCH_tasks_G[SCH_MAX_TASKS - 1].RunMe = 0;
    SCH_tasks_G[SCH_MAX_TASKS - 1].TaskID = 0;

    // Next one has no delay -> Run
    if (SCH_tasks_G[0].pTask != 0 && SCH_tasks_G[0].Delay == 0) {
            SCH_tasks_G[0].RunMe = 1;
        }

    return 1; //Success
}
