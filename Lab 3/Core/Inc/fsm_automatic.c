#include "fsm_automatic.h"
#include "traffic_light.h"
#include "led_display.h"
#include "timer.h"

enum State { INIT, GREEN_RED, YELLOW_RED, RED_GREEN, RED_YELLOW };
enum State traffic_state = INIT;

int red_time = 6;
int green_time = 4;
int yellow_time = 2;

void resetAutomaticFSM(void) {
    traffic_state = INIT;
}

void fsm_automatic_run(void) {
    // Mode 1: Counter down
    if (timer_second_flag == 1) {
        timer_second_flag = 0;
        if (countdown_led1 > 0) countdown_led1--;
        if (countdown_led2 > 0) countdown_led2--;
        update7SegBuffer(countdown_led1, countdown_led2);
    }

    switch (traffic_state) {
        case INIT:
            clearAllTrafficLights();
            traffic_state = GREEN_RED;
            setTraffic_0_Green_1_Red();
            setTimerTraffic(green_time * 1000);
            setTimerSecond(1000);

            countdown_led1 = green_time;
            countdown_led2 = red_time;
            update7SegBuffer(countdown_led1, countdown_led2);
            break;

        case GREEN_RED:
            if (timer_traffic_flag == 1) {
                traffic_state = YELLOW_RED;
                setTraffic_0_Yellow_1_Red();
                setTimerTraffic(yellow_time * 1000);

                countdown_led1 = yellow_time;
                countdown_led2 = yellow_time;
                update7SegBuffer(countdown_led1, countdown_led2);
            }
            break;

        case YELLOW_RED:
            if (timer_traffic_flag == 1) {
                traffic_state = RED_GREEN;
                setTraffic_0_Red_1_Green();
                setTimerTraffic(green_time * 1000);

                countdown_led1 = red_time;
                countdown_led2 = green_time;
                update7SegBuffer(countdown_led1, countdown_led2);
            }
            break;

        case RED_GREEN:
            if (timer_traffic_flag == 1) {
                traffic_state = RED_YELLOW;
                setTraffic_0_Red_1_Yellow();
                setTimerTraffic(yellow_time * 1000);

                countdown_led1 = yellow_time;
                countdown_led2 = yellow_time;
                update7SegBuffer(countdown_led1, countdown_led2);
            }
            break;

        case RED_YELLOW:
            if (timer_traffic_flag == 1) {
                traffic_state = GREEN_RED;
                setTraffic_0_Green_1_Red();
                setTimerTraffic(green_time * 1000);

                countdown_led1 = green_time;
                countdown_led2 = red_time;
                update7SegBuffer(countdown_led1, countdown_led2);
            }
            break;
    }
}
