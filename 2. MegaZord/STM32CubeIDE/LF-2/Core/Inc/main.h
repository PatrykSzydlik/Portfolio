/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
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
#include "stm32l0xx_hal.h"

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
#define Przycisk_Pin GPIO_PIN_14
#define Przycisk_GPIO_Port GPIOC
#define Przycisk_EXTI_IRQn EXTI4_15_IRQn
#define LED_0_Pin GPIO_PIN_8
#define LED_0_GPIO_Port GPIOA
#define LED_1_Pin GPIO_PIN_11
#define LED_1_GPIO_Port GPIOA
#define LED_2_Pin GPIO_PIN_12
#define LED_2_GPIO_Port GPIOA
#define L_PWM_Pin GPIO_PIN_15
#define L_PWM_GPIO_Port GPIOA
#define P_PWM_Pin GPIO_PIN_3
#define P_PWM_GPIO_Port GPIOB
#define L_2_Pin GPIO_PIN_4
#define L_2_GPIO_Port GPIOB
#define L_1_Pin GPIO_PIN_5
#define L_1_GPIO_Port GPIOB
#define P_2_Pin GPIO_PIN_6
#define P_2_GPIO_Port GPIOB
#define P_1_Pin GPIO_PIN_7
#define P_1_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/