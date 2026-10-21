#include "led_display.h"

static int led_buffer[4] = {0, 0, 0, 0};

static const uint8_t seg_code[10] = {
    0x40, // 0
    0x79, // 1
    0x24, // 2
    0x30, // 3
    0x19, // 4
    0x12, // 5
    0x02, // 6
    0x78, // 7
    0x00, // 8
    0x10  // 9
};

void display7SEG(int num) {
    if (num < 0 || num > 9) return;
    uint8_t code = seg_code[num];

    HAL_GPIO_WritePin(GPIOA, PA0_Pin, (code & 0x01) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOA, PA1_Pin, (code & 0x02) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOA, PA2_Pin, (code & 0x04) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOA, PA3_Pin, (code & 0x08) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOA, PA4_Pin, (code & 0x10) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOA, PA5_Pin, (code & 0x20) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOA, PA6_Pin, (code & 0x40) ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void update7SEG(int index) {
    HAL_GPIO_WritePin(GPIOA, EN0_Pin | EN1_Pin | EN2_Pin | EN3_Pin, EN_OFF);

    switch (index) {
        case 0:
            display7SEG(led_buffer[0]);
            HAL_GPIO_WritePin(GPIOA, EN0_Pin, EN_ON);
            break;
        case 1:
            display7SEG(led_buffer[1]);
            HAL_GPIO_WritePin(GPIOA, EN1_Pin, EN_ON);
            break;
        case 2:
            display7SEG(led_buffer[2]);
            HAL_GPIO_WritePin(GPIOA, EN2_Pin, EN_ON);
            break;
        case 3:
            display7SEG(led_buffer[3]);
            HAL_GPIO_WritePin(GPIOA, EN3_Pin, EN_ON);
            break;
        default:
            break;
    }
}

// Hàm cập nhật buffer: Xử lý hiển thị Value và Mode tách biệt
void update7SegBuffer(int val1, int val2) {
    // val1: Hiển thị ra 2 bóng bên trái (Hàng chục và đơn vị của Value)
    led_buffer[0] = val1 / 10;
    led_buffer[1] = val1 % 10;

    // val2: Hiển thị ra 2 bóng bên phải (Hàng chục và đơn vị của Mode hoặc Road 2)
    led_buffer[2] = val2 / 10;
    led_buffer[3] = val2 % 10;
}
