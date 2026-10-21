#ifndef INC_TRAFFIC_LIGHT_H_
#define INC_TRAFFIC_LIGHT_H_

#include "main.h"

#define LED_ON  GPIO_PIN_RESET
#define LED_OFF GPIO_PIN_SET

void clearAllTrafficLights(void);
void setTraffic_0_Red_1_Green(void);
void setTraffic_0_Red_1_Yellow(void);
void setTraffic_0_Green_1_Red(void);
void setTraffic_0_Yellow_1_Red(void);

// Hàm nháy đèn cho Mode 2, 3, 4
void toggleAllRedLEDs(void);
void toggleAllYellowLEDs(void);
void toggleAllGreenLEDs(void);

#endif /* INC_TRAFFIC_LIGHT_H_ */
