/*
 * VariableContrastLed.cpp
 *
 *  Created on: May 31, 2021
 *      Author: Javad Ramezanzadeh
 */

#include "VariableContrastLed.h"
#include "math.h"

VariableContrastLed::VariableContrastLed(TIM_HandleTypeDef *timer, uint32_t channel,
		uint16_t contrast, uint32_t OCPolarity) {
	// TODO Auto-generated constructor stub
	//TODO check the parameter
	mTimer = timer;
	mContrast = contrast;
	mChannel = channel;
	mOcPolarity = OCPolarity;

	HAL_TIM_Base_Start(mTimer);
	HAL_TIM_PWM_Start(mTimer, mChannel);
	setPulseWidth();

}

VariableContrastLed::~VariableContrastLed() {
	// TODO Auto-generated destructor stub
}

uint16_t VariableContrastLed::getContrast() const {
	return mContrast;
}

void VariableContrastLed::setContrast(uint16_t contrast) {
	mContrast = contrast;
	setPulseWidth();
}

void VariableContrastLed::setContrastPercentage(uint8_t percentage) {
	if(percentage > 100) percentage = 100;
	percentage /= 10;
	mContrast = 63*(pow(2, percentage) - 1);
	setPulseWidth();
}

void VariableContrastLed::setPulseWidth(void) {
	TIM_OC_InitTypeDef sConfigOC = {0};

	sConfigOC.OCMode = TIM_OCMODE_PWM1;
	sConfigOC.Pulse = mContrast;
	sConfigOC.OCPolarity = mOcPolarity;
	sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	HAL_TIM_PWM_Stop(mTimer, mChannel);
	if (HAL_TIM_PWM_ConfigChannel(mTimer, &sConfigOC, mChannel) != HAL_OK)
	{
		Error_Handler();
	}
	HAL_TIM_PWM_Start(mTimer, mChannel);
}
