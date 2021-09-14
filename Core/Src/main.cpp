/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "usb_device.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "VariableContrastLed.h"
#include "string.h"
#include "stdio.h"
#include "math.h"
#include "usbd_hid.h"
#include "UsbKeyboard.h"
#include "map"
#include "Debug.h"
#include "PowerStateMonitor.h"
#include "AisPowerController.h"
#include "KeyObserver.h"
#include "MkdPowerController.h"
#include "CommandListener.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
// HID Media

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
extern USBD_HandleTypeDef hUsbDeviceFS;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
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
	MX_TIM3_Init();
	//MX_UART5_Init();
	MX_USB_DEVICE_Init();
	MX_I2C1_Init();
	MX_I2C2_Init();
	MX_TIM4_Init();
	/* USER CODE BEGIN 2 */

	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */

	VariableContrastLed	backgroundLed(&htim3, TIM_CHANNEL_1, 0);

	UsbKeyboard::instance().init(&hUsbDeviceFS);

	GpioHandler 		mode0(MODE0_GPIO_Port, MODE0_Pin);
	GpioHandler 		mode1(MODE1_GPIO_Port, MODE1_Pin);
	GpioHandler 		plugIn(PLUG_IN_GPIO_Port, PLUG_IN_Pin);
	PowerStateMonitor	powerStateMonitor(&plugIn, &mode0, &mode1);

	GpioHandler			aisInputPwrCtrl(AIS_PWR_CTRL_GPIO_Port, AIS_PWR_CTRL_Pin);
	GpioHandler			ais3V8PwrCtrl(POWER_CTRL_3V8_GPIO_Port, POWER_CTRL_3V8_Pin);
	AisPowerController	aisPowerController(&aisInputPwrCtrl, &ais3V8PwrCtrl);
	powerStateMonitor.addObserver(aisPowerController);

	GpioHandler			mkd5VPwrCtrl(POWER_CTRL_5V_GPIO_Port, POWER_CTRL_5V_Pin);
	GpioHandler			mkd3V3PwrCtrl(POWER_CTRL_3V3_GPIO_Port, POWER_CTRL_3V3_Pin);
	VariableContrastLed	powerLed(&htim4, TIM_CHANNEL_3, 0, TIM_OCPOLARITY_LOW);
	VariableContrastLed	bgLed(&htim3, TIM_CHANNEL_1, 0, TIM_OCPOLARITY_HIGH);
	MkdPowerController 	mkdPowerController(&mkd3V3PwrCtrl, &mkd5VPwrCtrl, &powerLed, &bgLed);
	powerStateMonitor.addObserver(mkdPowerController);
	UsbKeyboard::instance().addObserver(mkdPowerController);

	CommandListener  cmdListener(&bgLed);

	Debug::getInstance() << "Starting application ...\r\n";

	uint32_t ledToggleTime = HAL_GetTick();

	while (1)
	{
		/* USER CODE END WHILE */

		/* USER CODE BEGIN 3 */
		if(HAL_GetTick() - ledToggleTime > 2000){

			ledToggleTime = HAL_GetTick();
		}

		UsbKeyboard::instance().run();
		powerStateMonitor.run();
		mkdPowerController.run();
		cmdListener.run();

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
	RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

	/** Initializes the RCC Oscillators according to the specified parameters
	 * in the RCC_OscInitTypeDef structure.
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL6;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	{
		Error_Handler();
	}
	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
			|RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
	{
		Error_Handler();
	}
	PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USB;
	PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_PLL_DIV1_5;
	if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
	{
		Error_Handler();
	}
}

/* USER CODE BEGIN 4 */
extern "C"{
typedef struct{
	uint8_t 		id;
	GPIO_TypeDef 	*port;
} KeyInfoType;
std::map<uint16_t, KeyInfoType> keysMap = {
		{KEY1_Pin, {Key_GOTO, 		KEY1_GPIO_Port}},
		{KEY2_Pin, {Key_WayPoint, 	KEY2_GPIO_Port}},
		{KEY3_Pin, {Key_Plus, 		KEY3_GPIO_Port}},
		{KEY4_Pin, {Key_Page, 		KEY4_GPIO_Port}},
		{KEY5_Pin, {Key_Minus, 		KEY5_GPIO_Port}},
		{KEY6_Pin, {Key_Right, 		KEY6_GPIO_Port}},
		{KEY7_Pin, {Key_UP, 		KEY7_GPIO_Port}},
		{KEY8_Pin, {Key_OK, 		KEY8_GPIO_Port}},
		{KEY9_Pin, {Key_Down, 		KEY9_GPIO_Port}},
		{KEY10_Pin, {Key_Left, 		KEY10_GPIO_Port}},
		{KEY11_Pin, {Key_Alt, 		KEY11_GPIO_Port}},
		{KEY12_Pin, {Key_Menu, 		KEY12_GPIO_Port}},
		{KEY13_Pin, {Key_Esc, 		KEY13_GPIO_Port}},
		{KEY14_Pin, {Key_MOB, 		KEY14_GPIO_Port}},
		{KEY15_Pin, {Key_Power, 	KEY15_GPIO_Port}},
};

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){

	if(HAL_GPIO_ReadPin(keysMap[GPIO_Pin].port, GPIO_Pin) == GPIO_PIN_RESET){
		//falling
		UsbKeyboard::instance().handleKeyEvent(keysMap[GPIO_Pin].id, KEY_PRESSED);
	}else{
		//rising
		UsbKeyboard::instance().handleKeyEvent(keysMap[GPIO_Pin].id, KEY_RELEASED);
	}
}

void HAL_I2C_SlaveRxCpltCallback(I2C_HandleTypeDef *hi2c){
	if(hi2c->Instance == I2C1){
		Debug::getInstance() << "I2C1 Data Received\r\n";
	}else if(hi2c->Instance == I2C2){

	}
}

void HAL_I2C_ErrorCallback(I2C_HandleTypeDef *hi2c){
	if(hi2c->ErrorCode != HAL_I2C_ERROR_NONE)
		Debug::getInstance() << "I2C Error[" <<hi2c->ErrorCode << "]\r\n";
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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
	/* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
