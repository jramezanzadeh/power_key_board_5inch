/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
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
#define KEY_DATA_A_Pin GPIO_PIN_0
#define KEY_DATA_A_GPIO_Port GPIOC
#define KEY_DATA_B_Pin GPIO_PIN_1
#define KEY_DATA_B_GPIO_Port GPIOC
#define KEY_DATA_C_Pin GPIO_PIN_2
#define KEY_DATA_C_GPIO_Port GPIOC
#define MODE0_Pin GPIO_PIN_3
#define MODE0_GPIO_Port GPIOC
#define KEY_DATA_D_Pin GPIO_PIN_0
#define KEY_DATA_D_GPIO_Port GPIOA
#define MODE1_Pin GPIO_PIN_1
#define MODE1_GPIO_Port GPIOA
#define KEY13_Pin GPIO_PIN_2
#define KEY13_GPIO_Port GPIOA
#define KEY13_EXTI_IRQn EXTI2_IRQn
#define KEY10_Pin GPIO_PIN_3
#define KEY10_GPIO_Port GPIOA
#define KEY10_EXTI_IRQn EXTI3_IRQn
#define KEY7_Pin GPIO_PIN_4
#define KEY7_GPIO_Port GPIOA
#define KEY7_EXTI_IRQn EXTI4_IRQn
#define KEY8_Pin GPIO_PIN_5
#define KEY8_GPIO_Port GPIOA
#define KEY8_EXTI_IRQn EXTI9_5_IRQn
#define KEY9_Pin GPIO_PIN_6
#define KEY9_GPIO_Port GPIOA
#define KEY9_EXTI_IRQn EXTI9_5_IRQn
#define KEY3_Pin GPIO_PIN_7
#define KEY3_GPIO_Port GPIOA
#define KEY3_EXTI_IRQn EXTI9_5_IRQn
#define POWER_CTRL_3V3_Pin GPIO_PIN_4
#define POWER_CTRL_3V3_GPIO_Port GPIOC
#define POWER_CTRL_5V_Pin GPIO_PIN_5
#define POWER_CTRL_5V_GPIO_Port GPIOC
#define KEY6_Pin GPIO_PIN_0
#define KEY6_GPIO_Port GPIOB
#define KEY6_EXTI_IRQn EXTI0_IRQn
#define KEY4_Pin GPIO_PIN_1
#define KEY4_GPIO_Port GPIOB
#define KEY4_EXTI_IRQn EXTI1_IRQn
#define AIS_PWR_CTRL_Pin GPIO_PIN_2
#define AIS_PWR_CTRL_GPIO_Port GPIOB
#define GAUGE_SCL_Pin GPIO_PIN_10
#define GAUGE_SCL_GPIO_Port GPIOB
#define GAUGE_SDA_Pin GPIO_PIN_11
#define GAUGE_SDA_GPIO_Port GPIOB
#define KEY5_Pin GPIO_PIN_12
#define KEY5_GPIO_Port GPIOB
#define KEY5_EXTI_IRQn EXTI15_10_IRQn
#define KEY1_Pin GPIO_PIN_13
#define KEY1_GPIO_Port GPIOB
#define KEY1_EXTI_IRQn EXTI15_10_IRQn
#define KEY2_Pin GPIO_PIN_14
#define KEY2_GPIO_Port GPIOB
#define KEY2_EXTI_IRQn EXTI15_10_IRQn
#define KEY15_Pin GPIO_PIN_15
#define KEY15_GPIO_Port GPIOB
#define KEY15_EXTI_IRQn EXTI15_10_IRQn
#define LED_KEY_PWM_Pin GPIO_PIN_6
#define LED_KEY_PWM_GPIO_Port GPIOC
#define PLUG_IN_Pin GPIO_PIN_7
#define PLUG_IN_GPIO_Port GPIOC
#define POWER_CTRL_3V8_Pin GPIO_PIN_9
#define POWER_CTRL_3V8_GPIO_Port GPIOC
#define KEY12_Pin GPIO_PIN_8
#define KEY12_GPIO_Port GPIOA
#define KEY12_EXTI_IRQn EXTI9_5_IRQn
#define KEY11_Pin GPIO_PIN_9
#define KEY11_GPIO_Port GPIOA
#define KEY11_EXTI_IRQn EXTI9_5_IRQn
#define KEY14_Pin GPIO_PIN_10
#define KEY14_GPIO_Port GPIOA
#define KEY14_EXTI_IRQn EXTI15_10_IRQn
#define USB_DM_Pin GPIO_PIN_11
#define USB_DM_GPIO_Port GPIOA
#define USB_DP_Pin GPIO_PIN_12
#define USB_DP_GPIO_Port GPIOA
#define BATT_ALERT_Pin GPIO_PIN_11
#define BATT_ALERT_GPIO_Port GPIOC
#define UART5_TX_Pin GPIO_PIN_12
#define UART5_TX_GPIO_Port GPIOC
#define UART5_RX_Pin GPIO_PIN_2
#define UART5_RX_GPIO_Port GPIOD
#define BATT_CHRG_Pin GPIO_PIN_4
#define BATT_CHRG_GPIO_Port GPIOB
#define LED_Pin GPIO_PIN_5
#define LED_GPIO_Port GPIOB
#define LED_PWR_PWM_Pin GPIO_PIN_8
#define LED_PWR_PWM_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
