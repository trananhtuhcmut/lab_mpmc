/* Includes ------------------------------------------------------------------*/
#include "main.h"

void SystemClock_Config(void);
static void MX_GPIO_Init(void);


//Array for number displayment NS
void display7SEG_NS(int num)
{
    if (num < 0 || num > 9) return;
    uint8_t segmentData[10][7] = {
        {0, 0, 0, 0, 0, 0, 1}, // 0
        {1, 0, 0, 1, 1, 1, 1}, // 1
        {0, 0, 1, 0, 0, 1, 0}, // 2
        {0, 0, 0, 0, 1, 1, 0}, // 3
        {1, 0, 0, 1, 1, 0, 0}, // 4
        {0, 1, 0, 0, 1, 0, 0}, // 5
        {0, 1, 0, 0, 0, 0, 0}, // 6
        {0, 0, 0, 1, 1, 1, 1}, // 7
        {0, 0, 0, 0, 0, 0, 0}, // 8
        {0, 0, 0, 0, 1, 0, 0}  // 9
    };

    HAL_GPIO_WritePin(GPIOA, a_Pin, segmentData[num][0]);
    HAL_GPIO_WritePin(GPIOA, b_Pin, segmentData[num][1]);
    HAL_GPIO_WritePin(GPIOA, c_Pin, segmentData[num][2]);
    HAL_GPIO_WritePin(GPIOA, d_Pin, segmentData[num][3]);
    HAL_GPIO_WritePin(GPIOA, e_Pin, segmentData[num][4]);
    HAL_GPIO_WritePin(GPIOA, f_Pin, segmentData[num][5]);
    HAL_GPIO_WritePin(GPIOA, g_Pin, segmentData[num][6]);
}

// Array for number displayment EW
void display7SEG_EW(int num)
{
    if (num < 0 || num > 9) return;
    uint8_t segmentData[10][7] = {
        {0, 0, 0, 0, 0, 0, 1}, // 0
        {1, 0, 0, 1, 1, 1, 1}, // 1
        {0, 0, 1, 0, 0, 1, 0}, // 2
        {0, 0, 0, 0, 1, 1, 0}, // 3
        {1, 0, 0, 1, 1, 0, 0}, // 4
        {0, 1, 0, 0, 1, 0, 0}, // 5
        {0, 1, 0, 0, 0, 0, 0}, // 6
        {0, 0, 0, 1, 1, 1, 1}, // 7
        {0, 0, 0, 0, 0, 0, 0}, // 8
        {0, 0, 0, 0, 1, 0, 0}  // 9
    };

    HAL_GPIO_WritePin(GPIOA, a1_Pin, segmentData[num][0]);
    HAL_GPIO_WritePin(GPIOA, b1_Pin, segmentData[num][1]);
    HAL_GPIO_WritePin(GPIOA, c1_Pin, segmentData[num][2]);
    HAL_GPIO_WritePin(GPIOA, d1_Pin, segmentData[num][3]);
    HAL_GPIO_WritePin(GPIOA, e1_Pin, segmentData[num][4]);
    HAL_GPIO_WritePin(GPIOA, f1_Pin, segmentData[num][5]);
    HAL_GPIO_WritePin(GPIOA, g1_Pin, segmentData[num][6]);
}

int main(void)
{
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();

  while (1)
  {
      // Initial (off)
      HAL_GPIO_WritePin(GPIOB, LED_RED_Pin | LED_YELLOW_Pin, GPIO_PIN_SET);
      HAL_GPIO_WritePin(GPIOB, LED_GREEN1_Pin | LED_YELLOW1_Pin, GPIO_PIN_SET);

      // NS green (3s) | EW red (5 to 3)
      HAL_GPIO_WritePin(GPIOB, LED_GREEN_Pin, GPIO_PIN_RESET);
      HAL_GPIO_WritePin(GPIOB, LED_RED1_Pin, GPIO_PIN_RESET);
      for (int i = 0; i < 3; i++) {
          display7SEG_NS(3 - i);
          display7SEG_EW(5 - i);
          HAL_Delay(1000);
      }


      // NS green to yellow (2s) | EW still red
      HAL_GPIO_WritePin(GPIOB, LED_GREEN_Pin, GPIO_PIN_SET);
      HAL_GPIO_WritePin(GPIOB, LED_YELLOW_Pin, GPIO_PIN_RESET);
      for (int i = 0; i < 2; i++) {
          display7SEG_NS(2 - i);
          display7SEG_EW(2 - i);
          HAL_Delay(1000);
      }

      // NS yellow to red  (5 to 3) | EW red to green (3s)
      HAL_GPIO_WritePin(GPIOB, LED_YELLOW_Pin, GPIO_PIN_SET);
      HAL_GPIO_WritePin(GPIOB, LED_RED_Pin, GPIO_PIN_RESET);

      HAL_GPIO_WritePin(GPIOB, LED_RED1_Pin, GPIO_PIN_SET);
      HAL_GPIO_WritePin(GPIOB, LED_GREEN1_Pin, GPIO_PIN_RESET);

      for (int i = 0; i < 3; i++) {
          display7SEG_NS(5 - i);
          display7SEG_EW(3 - i);
          HAL_Delay(1000);
      }

      // NS Red (2 to 1) | EW yellow (2s)
      HAL_GPIO_WritePin(GPIOB, LED_GREEN1_Pin, GPIO_PIN_SET);    // Tắt Xanh ngang
      HAL_GPIO_WritePin(GPIOB, LED_YELLOW1_Pin, GPIO_PIN_RESET); // Bật Vàng ngang

      for (int i = 0; i < 2; i++) {
          display7SEG_NS(2 - i);
          display7SEG_EW(2 - i);
          HAL_Delay(1000);
      }
  }
  /* USER CODE END WHILE */
}
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, a_Pin|b_Pin|c_Pin|d_Pin
                          |e_Pin|f_Pin|g_Pin|a1_Pin
                          |b1_Pin|c1_Pin|d1_Pin|e1_Pin
                          |f1_Pin|g1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LED_RED_Pin|LED_GREEN_Pin|LED_YELLOW_Pin|LED_RED1_Pin
                          |LED_YELLOW1_Pin|LED_GREEN1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : a_Pin b_Pin c_Pin d_Pin
                           e_Pin f_Pin g_Pin a1_Pin
                           b1_Pin c1_Pin d1_Pin e1_Pin
                           f1_Pin g1_Pin */
  GPIO_InitStruct.Pin = a_Pin|b_Pin|c_Pin|d_Pin
                          |e_Pin|f_Pin|g_Pin|a1_Pin
                          |b1_Pin|c1_Pin|d1_Pin|e1_Pin
                          |f1_Pin|g1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : LED_RED_Pin LED_GREEN_Pin LED_YELLOW_Pin LED_RED1_Pin
                           LED_YELLOW1_Pin LED_GREEN1_Pin */
  GPIO_InitStruct.Pin = LED_RED_Pin|LED_GREEN_Pin|LED_YELLOW_Pin|LED_RED1_Pin
                          |LED_YELLOW1_Pin|LED_GREEN1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
