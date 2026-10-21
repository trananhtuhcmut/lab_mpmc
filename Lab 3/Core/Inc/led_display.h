#ifndef INC_LED_DISPLAY_H_
#define INC_LED_DISPLAY_H_

#include "main.h"

#define EN_ON   GPIO_PIN_SET
#define EN_OFF  GPIO_PIN_RESET

void display7SEG(int num);
void update7SEG(int index);
void update7SegBuffer(int val_road1, int val_road2);

#endif /* INC_LED_DISPLAY_H_ */
