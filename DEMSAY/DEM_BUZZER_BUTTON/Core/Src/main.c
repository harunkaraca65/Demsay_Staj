/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "DigitalInputOutputs.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
uint8_t counter = 0;
uint8_t rgbcounter = 0;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
RTC_HandleTypeDef hrtc;

/* USER CODE BEGIN PV */
volatile uint64_t SYSTickTimer = 0;
SystemClockTimer_t SysClkTim;  // Gerçek tanımlama burada!
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_RTC_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_RTC_Init();
  /* USER CODE BEGIN 2 */
  RGB_LED_Control(Active, Passive, Passive);
  LED_Control(Active, Passive, Passive, Passive, Passive);
  Buzzer_Control(Active);
  HAL_Delay(500);
  RGB_LED_Control(Passive, Active, Passive);
  LED_Control(Active, Active, Passive, Passive, Passive);
  Buzzer_Control(Passive);
  HAL_Delay(500);
  RGB_LED_Control(Passive, Passive, Active);
  LED_Control(Active, Active, Active, Passive, Passive);
  Buzzer_Control(Active);
  HAL_Delay(500);
  RGB_LED_Control(Active, Active, Active);
  LED_Control(Active, Active, Active, Active, Passive);
  Buzzer_Control(Passive);
  HAL_Delay(500);
  LED_Control(Active, Active, Active, Active, Active);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		if (HAL_GPIO_ReadPin(BUTON_1_GPIO_Port, BUTON_1_Pin) == 1)
				HAL_GPIO_WritePin(LED1_RED_GPIO_Port, LED1_RED_Pin, 0);
			else
				HAL_GPIO_WritePin(LED1_RED_GPIO_Port, LED1_RED_Pin, 1);

			if (HAL_GPIO_ReadPin(BUTON_2_GPIO_Port, BUTON_2_Pin) == 1)
				HAL_GPIO_WritePin(LED2_GREEN_GPIO_Port, LED2_GREEN_Pin, 0);
			else
				HAL_GPIO_WritePin(LED2_GREEN_GPIO_Port, LED2_GREEN_Pin, 1);

			if (HAL_GPIO_ReadPin(BUTON_3_GPIO_Port, BUTON_3_Pin) == 1)
				HAL_GPIO_WritePin(LED3_BLUE_GPIO_Port, LED3_BLUE_Pin, 0);
			else
				HAL_GPIO_WritePin(LED3_BLUE_GPIO_Port, LED3_BLUE_Pin, 1);


			if (SysClkTim._1000sn == 1) {
				if (rgbcounter > 4) {
					rgbcounter = 0;
				}
				switch (rgbcounter) {
				case 0:
					HAL_GPIO_WritePin(RGB_R_GPIO_Port, RGB_R_Pin, 1);
					HAL_GPIO_WritePin(RGB_G_GPIO_Port, RGB_G_Pin, 0);
					HAL_GPIO_WritePin(RGB_B_GPIO_Port, RGB_B_Pin, 0);
					break;
				case 1:
					HAL_GPIO_WritePin(RGB_R_GPIO_Port, RGB_R_Pin, 0);
					HAL_GPIO_WritePin(RGB_G_GPIO_Port, RGB_G_Pin, 1);
					HAL_GPIO_WritePin(RGB_B_GPIO_Port, RGB_B_Pin, 0);
					break;
				case 2:
					HAL_GPIO_WritePin(RGB_R_GPIO_Port, RGB_R_Pin, 0);
					HAL_GPIO_WritePin(RGB_G_GPIO_Port, RGB_G_Pin, 0);
					HAL_GPIO_WritePin(RGB_B_GPIO_Port, RGB_B_Pin, 1);
					break;
				case 3:
					HAL_GPIO_WritePin(RGB_R_GPIO_Port, RGB_R_Pin, 1);
					HAL_GPIO_WritePin(RGB_G_GPIO_Port, RGB_G_Pin, 1);
					HAL_GPIO_WritePin(RGB_B_GPIO_Port, RGB_B_Pin, 1);
					break;
				case 4:
					HAL_GPIO_WritePin(RGB_R_GPIO_Port, RGB_R_Pin, 0);
					HAL_GPIO_WritePin(RGB_G_GPIO_Port, RGB_G_Pin, 0);
					HAL_GPIO_WritePin(RGB_B_GPIO_Port, RGB_B_Pin, 0);
					break;
				}

				rgbcounter++;

				SysClkTim._1000sn = 0;
			}
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
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
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_LSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSIDiv = RCC_HSI_DIV1;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief RTC Initialization Function
  * @param None
  * @retval None
  */
static void MX_RTC_Init(void)
{

  /* USER CODE BEGIN RTC_Init 0 */

  /* USER CODE END RTC_Init 0 */

  /* USER CODE BEGIN RTC_Init 1 */

  /* USER CODE END RTC_Init 1 */

  /** Initialize RTC Only
  */
  hrtc.Instance = RTC;
  hrtc.Init.HourFormat = RTC_HOURFORMAT_24;
  hrtc.Init.AsynchPrediv = 127;
  hrtc.Init.SynchPrediv = 255;
  hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
  hrtc.Init.OutPutRemap = RTC_OUTPUT_REMAP_NONE;
  hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
  hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
  hrtc.Init.OutPutPullUp = RTC_OUTPUT_PULLUP_NONE;
  if (HAL_RTC_Init(&hrtc) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN RTC_Init 2 */

  /* USER CODE END RTC_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, RGB_R_Pin|RGB_G_Pin|LED1_RED_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, BUZZER_Pin|RGB_B_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, LED2_GREEN_Pin|LED3_BLUE_Pin|LED4_WHITE_Pin|LED5_YELLOW_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : RGB_R_Pin RGB_G_Pin LED1_RED_Pin */
  GPIO_InitStruct.Pin = RGB_R_Pin|RGB_G_Pin|LED1_RED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : BUTON_1_Pin BUTON_2_Pin BUTON_3_Pin */
  GPIO_InitStruct.Pin = BUTON_1_Pin|BUTON_2_Pin|BUTON_3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : BUZZER_Pin RGB_B_Pin */
  GPIO_InitStruct.Pin = BUZZER_Pin|RGB_B_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : LED2_GREEN_Pin LED3_BLUE_Pin LED4_WHITE_Pin LED5_YELLOW_Pin */
  GPIO_InitStruct.Pin = LED2_GREEN_Pin|LED3_BLUE_Pin|LED4_WHITE_Pin|LED5_YELLOW_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
void HAL_SYSTICK_Callback(void) {
SYSTickTimer++;

if (SYSTickTimer % 1 == 0) {
SysClkTim._1msn = 1;
}
if (SYSTickTimer % 10 == 0) {
SysClkTim._10msn = 1;
}
if (SYSTickTimer % 50 == 0) {
SysClkTim._50msn = 1;
}
if (SYSTickTimer % 100 == 0) {
SysClkTim._100msn = 1;
}
if (SYSTickTimer % 250 == 0) {
SysClkTim._250msn = 1;
}
if (SYSTickTimer % 500 == 0) {
SysClkTim._500msn = 1;
}
if (SYSTickTimer % 1000 == 0) {
SysClkTim._1000sn = 1;
}
if (SYSTickTimer % 2000 == 0) {
SysClkTim._2000sn = 1;
}
if (SYSTickTimer % 5000 == 0) {
SysClkTim._5000sn = 1;
}
}
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
