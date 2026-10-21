#ifndef INC_TIMER_H_
#define INC_TIMER_H_

#include "main.h"

// 10ms Interpupt
#define TIMER_CYCLE 10

extern int timer_traffic_flag;
extern int timer_second_flag;
extern int timer_7seg_flag;
extern int timer_blink_flag; //  2Hz cho Mode 2, 3, 4

extern int countdown_led1;
extern int countdown_led2;

void setTimerTraffic(int duration);
void setTimerSecond(int duration);
void setTimer7Seg(int duration);
void setTimerBlink(int duration);
void timerRun(void);

#endif /* INC_TIMER_H_ */
