/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : LEDS sequence in the NUCLEO-F411RE board
  ******************************************************************************
  * @attention
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "leds.h"
#include "keyboard.h"
#include "sequences.h"

/* Variables declaration -----------------------------------------------------*/
enum states{normal, disconnected, alarm};

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);

enum states normalOperation( struct sequence_t *control, uint16_t *ledsPin, GPIO_TypeDef *ledsPort[] );
enum states disconnOperation( struct sequence_t *control, uint16_t *ledsPin, GPIO_TypeDef *ledsPort[] );
enum states alarmOperation( struct sequence_t *control, uint16_t *ledsPin, GPIO_TypeDef *ledsPort[] );

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void){
	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();
	/* Configure the system clock */
	SystemClock_Config();
	/* Initialize all configured peripherals */
	MX_GPIO_Init();

	/*---- Variables definition for normal operation of the traffic light -----*/
	uint16_t ledsPinNormal[] = {LED_GREEN_Pin, LED_YELLOW_Pin, LED_RED_Pin};
	GPIO_TypeDef ledsPortNormal[] = {LED_GREEN_GPIO_Port, LED_YELLOW_GPIO_Port, LED_RED_GPIO_Port};
	uint32_t seqTimesNormal[] = {3000, 500, 1500};
	uint8_t pos = 0;
	uint8_t lenNormal = sizeof(ledsPinNormal)/sizeof(*ledsPinNormal);
	enum states state;
	struct sequence_t psequenceNormal;
	sequenceActivation(&psequenceNormal, &ledsPinNormal, ledsPortNormal, &seqTimesNormal, pos, lenNormal);
	/*-------------------------------------------------------------------------*/

	/*- Variables definition for disconnected operation of the traffic light --*/
	uint16_t ledsPinDisconn[] = {LED_YELLOW_Pin, BLACKOUT};
	GPIO_TypeDef ledsPortDisconn[] = {LED_YELLOW_GPIO_Port, BLACKOUT};
	uint32_t seqTimesDisconn[] = {500, 500};
	uint8_t lenDisconn = sizeof(ledsPinDisconn)/sizeof(*ledsPinDisconn);
	struct sequence_t psequenceDisconn;
	sequenceActivation(&psequenceDisconn, &ledsPinDisconn, ledsPortDisconn, &seqTimesDisconn, pos, lenDisconn);
	/*-------------------------------------------------------------------------*/

	/*- Variables definition for disconnected operation of the traffic light --*/
	uint16_t ledsPinAlarm[] = {LED_RED_Pin, BLACKOUT};
	GPIO_TypeDef ledsPortAlarm[] = {LED_RED_GPIO_Port, BLACKOUT};
	uint32_t seqTimesAlarm[] = {500, 500};
	uint8_t lenAlarm = sizeof(ledsPinAlarm)/sizeof(*ledsPinAlarm);
	struct sequence_t psequenceAlarm;
	sequenceActivation(&psequenceAlarm, &ledsPinAlarm, ledsPortAlarm, &seqTimesAlarm, pos, lenAlarm);
	/*-------------------------------------------------------------------------*/
	state = normal;

	/* Infinite loop */
	while (1){
		switch (state){
		case normal:
			state = normalOperation(&psequenceNormal, ledsPinNormal, ledsPortNormal);
			break;
		case disconnected:
			state = disconnOperation(&psequenceDisconn, ledsPinDisconn, ledsPortDisconn);
			break;
		case alarm:
			state = alarmOperation(&psequenceAlarm, ledsPinAlarm, ledsPortAlarm);
			break;
		}
		//sequenceActualization(&psequenceNormal, ledsPinNormal, ledsPortNormal);
		//sequenceActualization(&psequenceDisconn, ledsPinDisconn, ledsPortDisconn);
		//sequenceActualization(&psequenceAlarm, ledsPinAlarm, ledsPortAlarm);
	}
	return 0;
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
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
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LED_RED_Pin|LED_BLUE_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED_YELLOW_GPIO_Port, LED_YELLOW_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : KEY1_Pin */
  GPIO_InitStruct.Pin = KEY1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(KEY1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : LED_RED_Pin LED_BLUE_Pin */
  GPIO_InitStruct.Pin = LED_RED_Pin|LED_BLUE_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : LED_GREEN_Pin */
  GPIO_InitStruct.Pin = LED_GREEN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED_GREEN_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LED_YELLOW_Pin */
  GPIO_InitStruct.Pin = LED_YELLOW_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED_YELLOW_GPIO_Port, &GPIO_InitStruct);

}

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
	  HAL_GPIO_TogglePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin);
	  HAL_Delay(500);
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

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
enum states normalOperation( struct sequence_t *control, uint16_t *ledsPin, GPIO_TypeDef *ledsPort[] ){
	enum states state = normal;
	if ( readKey(KEY1_GPIO_Port, KEY1_Pin) ){
		state = disconnected;
	}
	sequenceActualization(control, &ledsPin, ledsPort);
	return state;
}

enum states disconnOperation( struct sequence_t *control, uint16_t *ledsPin, GPIO_TypeDef *ledsPort[] ){
	enum states state = disconnected;
	if ( readKey(KEY1_GPIO_Port, KEY1_Pin) ){
		state = alarm;
	}
	sequenceActualization(control, &ledsPin, ledsPort);
	return state;
}

enum states alarmOperation( struct sequence_t *control, uint16_t *ledsPin, GPIO_TypeDef *ledsPort[] ){
	enum states state = alarm;
	if ( readKey(KEY1_GPIO_Port, KEY1_Pin) ){
		state = normal;
	}
	sequenceActualization(control, &ledsPin, ledsPort);
	return state;
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
