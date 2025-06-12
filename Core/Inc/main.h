/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g0xx_hal.h"

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

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define BUZZER_Pin GPIO_PIN_8
#define BUZZER_GPIO_Port GPIOB
#define RELAY_Pin GPIO_PIN_9
#define RELAY_GPIO_Port GPIOB
#define switch_Pin GPIO_PIN_15
#define switch_GPIO_Port GPIOC
#define i2c_scl_Pin GPIO_PIN_1
#define i2c_scl_GPIO_Port GPIOA
#define i2c_sda_Pin GPIO_PIN_2
#define i2c_sda_GPIO_Port GPIOA
#define DIPS1_A_Pin GPIO_PIN_3
#define DIPS1_A_GPIO_Port GPIOA
#define DIPS2_A_Pin GPIO_PIN_4
#define DIPS2_A_GPIO_Port GPIOA
#define DIPS3_A_Pin GPIO_PIN_5
#define DIPS3_A_GPIO_Port GPIOA
#define BUT1_Pin GPIO_PIN_7
#define BUT1_GPIO_Port GPIOA
#define BUT2_Pin GPIO_PIN_8
#define BUT2_GPIO_Port GPIOA
#define BUT3_Pin GPIO_PIN_11
#define BUT3_GPIO_Port GPIOA
#define BUT4_Pin GPIO_PIN_12
#define BUT4_GPIO_Port GPIOA
#define DP2_Pin GPIO_PIN_3
#define DP2_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
