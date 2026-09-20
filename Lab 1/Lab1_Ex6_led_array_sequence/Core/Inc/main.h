/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define pin1_Pin GPIO_PIN_4
#define pin1_GPIO_Port GPIOA
#define pin2_Pin GPIO_PIN_5
#define pin2_GPIO_Port GPIOA
#define pin3_Pin GPIO_PIN_6
#define pin3_GPIO_Port GPIOA
#define pin4_Pin GPIO_PIN_7
#define pin4_GPIO_Port GPIOA
#define pin5_Pin GPIO_PIN_8
#define pin5_GPIO_Port GPIOA
#define pin6_Pin GPIO_PIN_9
#define pin6_GPIO_Port GPIOA
#define pin7_Pin GPIO_PIN_10
#define pin7_GPIO_Port GPIOA
#define pin8_Pin GPIO_PIN_11
#define pin8_GPIO_Port GPIOA
#define pin9_Pin GPIO_PIN_12
#define pin9_GPIO_Port GPIOA
#define pin10_Pin GPIO_PIN_13
#define pin10_GPIO_Port GPIOA
#define pin11_Pin GPIO_PIN_14
#define pin11_GPIO_Port GPIOA
#define pin12_Pin GPIO_PIN_15
#define pin12_GPIO_Port GPIOA
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
