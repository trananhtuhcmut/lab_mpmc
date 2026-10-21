#include "main.h"
#include "input_reading.h"
#include "input_processing.h"
#include "fsm_automatic.h"
#include "traffic_light.h"
#include "led_display.h"
#include "timer.h"

//3 States
enum ButtonState { BUTTON_RELEASED, BUTTON_PRESSED, BUTTON_PRESSED_MORE_THAN_1_SECOND };
static enum ButtonState buttonState[3] = {BUTTON_RELEASED, BUTTON_RELEASED, BUTTON_RELEASED};

//4 Modes (0,1,2,3)
enum SystemMode { MODE_1_NORMAL = 1, MODE_2_RED = 2, MODE_3_YELLOW = 3, MODE_4_GREEN = 4 };
static enum SystemMode current_mode = MODE_1_NORMAL;

static int temp_value = 1;
static int index_led = 0;  // For 4 LED 7 segments

// Press downn
//static int is_button_just_pressed(int index) {
//    switch (buttonState[index]) {
//        case BUTTON_RELEASED:
//            if (is_button_pressed(index)) {
//                buttonState[index] = BUTTON_PRESSED;
//                return 1;
//            }
//            break;
//        case BUTTON_PRESSED:
//            if (!is_button_pressed(index)) {
//                buttonState[index] = BUTTON_RELEASED;
//            } else if (is_button_pressed_1s(index)) {
//                buttonState[index] = BUTTON_PRESSED_MORE_THAN_1_SECOND;
//            }
//            break;
//        case BUTTON_PRESSED_MORE_THAN_1_SECOND:
//            if (!is_button_pressed(index)) {
//                buttonState[index] = BUTTON_RELEASED;
//            }
//            break;
//    }
//    return 0;
//}

//Press + Hold Check
static int check_button_action(int index) {
    switch (buttonState[index]) {
        case BUTTON_RELEASED:
            if (is_button_pressed(index)) {
                buttonState[index] = BUTTON_PRESSED;
                return 0;
            }
            break;

        case BUTTON_PRESSED:
            if (!is_button_pressed(index)) {
                buttonState[index] = BUTTON_RELEASED;
                return 1;
            } else if (is_button_pressed_1s(index)) {
                buttonState[index] = BUTTON_PRESSED_MORE_THAN_1_SECOND;
                return 5;
            }
            break;

        case BUTTON_PRESSED_MORE_THAN_1_SECOND:
            if (!is_button_pressed(index)) {
                buttonState[index] = BUTTON_RELEASED;
                return 0;
            } else if (is_button_pressed_1s(index)) {
                return 5;
            }
            break;
    }
    return 0;
}

// Balance (Red=Yellow+Red)
static void auto_balance_time(enum SystemMode modified_mode) {
    // 1. Limit yellow
    if (yellow_time > 4) {
        yellow_time = 4;
    }

    // 2. Balance
    if (modified_mode == MODE_2_RED) {
        // Set Red -> Recalculate Green
        if (red_time <= yellow_time) {
            red_time = yellow_time + 1; // Minimize Green
        }
        green_time = red_time - yellow_time;
    }
    else if (modified_mode == MODE_3_YELLOW || modified_mode == MODE_4_GREEN) {
        // Set Green or Yellow -> Add to Red
        red_time = green_time + yellow_time;

        // 3 digits fix
        if (red_time > 99) {
            red_time = 99;
            if (modified_mode == MODE_4_GREEN) {
                green_time = red_time - yellow_time;
            }
        }
    }
}


void fsm_for_input_processing(void) {
    if (timer_7seg_flag == 1) {
        setTimer7Seg(10);
        update7SEG(index_led);
        index_led++;
        if (index_led >= 4) index_led = 0;
    }

    // Mode
    if (check_button_action(0) > 0) {
        clearAllTrafficLights();
        setTimerBlink(250);
        if (current_mode == MODE_1_NORMAL) {
            current_mode = MODE_2_RED;
            temp_value = red_time;
            update7SegBuffer(temp_value, MODE_2_RED);
        } else if (current_mode == MODE_2_RED) {
            current_mode = MODE_3_YELLOW;
            temp_value = yellow_time;
            update7SegBuffer(temp_value, MODE_3_YELLOW);
        } else if (current_mode == MODE_3_YELLOW) {
            current_mode = MODE_4_GREEN;
            temp_value = green_time;
            update7SegBuffer(temp_value, MODE_4_GREEN);
        } else {
            current_mode = MODE_1_NORMAL;
            resetAutomaticFSM();
        }
    }


    int add_val = 0;
    switch (current_mode) {
        case MODE_1_NORMAL:
            check_button_action(1);
            check_button_action(2);
            fsm_automatic_run();
            break;

        case MODE_2_RED:
            if (timer_blink_flag == 1) {
                setTimerBlink(250);
                toggleAllRedLEDs();
            }
            // Nút 1: Tăng thời gian
            add_val = check_button_action(1);
            if (add_val > 0) {
                temp_value += add_val;
                if (temp_value > 99) temp_value = 1;
                update7SegBuffer(temp_value, MODE_2_RED);
            }
            // Nút 2: Lưu
            if (check_button_action(2) > 0) {
                red_time = temp_value;
                auto_balance_time(MODE_2_RED);
            }
            break;

        case MODE_3_YELLOW:
            if (timer_blink_flag == 1) {
                setTimerBlink(250);
                toggleAllYellowLEDs();
            }
            add_val = check_button_action(1);
            if (add_val > 0) {
                temp_value += add_val;
                if (temp_value > 99) temp_value = 1;
                update7SegBuffer(temp_value, MODE_3_YELLOW);
            }
            if (check_button_action(2) > 0) {
                yellow_time = temp_value;
                auto_balance_time(MODE_3_YELLOW);
            }
            break;

        case MODE_4_GREEN:
            if (timer_blink_flag == 1) {
                setTimerBlink(250);
                toggleAllGreenLEDs();
            }
            add_val = check_button_action(1);
            if (add_val > 0) {
                temp_value += add_val;
                if (temp_value > 99) temp_value = 1;
                update7SegBuffer(temp_value, MODE_4_GREEN);
            }
            if (check_button_action(2) > 0) {
                green_time = temp_value;
                auto_balance_time(MODE_4_GREEN);
            }
            break;
    }
}
