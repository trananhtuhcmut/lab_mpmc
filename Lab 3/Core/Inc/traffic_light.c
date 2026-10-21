#include "traffic_light.h"

void clearAllTrafficLights(void) {
    HAL_GPIO_WritePin(GPIOB, RED0_Pin | YELLOW0_Pin | GREEN0_Pin, LED_OFF);
    HAL_GPIO_WritePin(GPIOB, RED1_Pin | YELLOW1_Pin | GREEN1_Pin, LED_OFF);
}

void setTraffic_0_Green_1_Red(void) {
    clearAllTrafficLights();
    HAL_GPIO_WritePin(GPIOB, GREEN0_Pin | RED1_Pin, LED_ON);
}

void setTraffic_0_Yellow_1_Red(void) {
    clearAllTrafficLights();
    HAL_GPIO_WritePin(GPIOB, YELLOW0_Pin | RED1_Pin, LED_ON);
}

void setTraffic_0_Red_1_Green(void) {
    clearAllTrafficLights();
    HAL_GPIO_WritePin(GPIOB, RED0_Pin | GREEN1_Pin, LED_ON);
}

void setTraffic_0_Red_1_Yellow(void) {
    clearAllTrafficLights();
    HAL_GPIO_WritePin(GPIOB, RED0_Pin | YELLOW1_Pin, LED_ON);
}

void toggleAllRedLEDs(void) {
    HAL_GPIO_TogglePin(GPIOB, RED0_Pin | RED1_Pin);
}

void toggleAllYellowLEDs(void) {
    HAL_GPIO_TogglePin(GPIOB, YELLOW0_Pin | YELLOW1_Pin);
}

void toggleAllGreenLEDs(void) {
    HAL_GPIO_TogglePin(GPIOB, GREEN0_Pin | GREEN1_Pin);
}
