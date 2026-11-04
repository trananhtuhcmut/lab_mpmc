#include "main.h"
#include "timer.h"
#include "input_reading.h"

int timer_traffic_counter = 0;
int timer_traffic_flag = 0;

int timer_second_counter = 1000 / TIMER_CYCLE;
int timer_second_flag = 0;

int timer_7seg_counter;
int timer_7seg_flag = 1;

int timer_blink_counter = 250 / TIMER_CYCLE;
int timer_blink_flag = 0;

int countdown_led1 = 0;
int countdown_led2 = 0;

void setTimerTraffic(int duration) {
    timer_traffic_counter = duration / TIMER_CYCLE;
    timer_traffic_flag = 0;
}

void setTimerSecond(int duration) {
    timer_second_counter = duration / TIMER_CYCLE;
    timer_second_flag = 0;
}

void setTimer7Seg(int duration) {
    timer_7seg_counter = duration / TIMER_CYCLE;
    timer_7seg_flag = 0;
}

void setTimerBlink(int duration) {
    timer_blink_counter = duration / TIMER_CYCLE;
    timer_blink_flag = 0;
}

void timerRun(void) {
    if (timer_traffic_counter > 0) {
        timer_traffic_counter--;
        if (timer_traffic_counter <= 0) timer_traffic_flag = 1;
    }

    if (timer_second_counter > 0) {
        timer_second_counter--;
        if (timer_second_counter <= 0) {
            timer_second_flag = 1;
            timer_second_counter = 1000 / TIMER_CYCLE;
        }
    }

    if (timer_7seg_counter > 0) {
        timer_7seg_counter--;
        if (timer_7seg_counter <= 0) timer_7seg_flag = 1;
    }

    if (timer_blink_counter > 0) {
        timer_blink_counter--;
        if (timer_blink_counter <= 0) timer_blink_flag = 1;
    }
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    if (htim->Instance == TIM2) {
        button_reading();
        timerRun();
    }
}
