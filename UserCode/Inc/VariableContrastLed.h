/*
 * VariableContrastLed.h
 *
 *  Created on: May 31, 2021
 *      Author: Javad Ramezanzadeh
 */

#ifndef VARIABLECONTRASTLED_H_
#define VARIABLECONTRASTLED_H_
#include "tim.h"

class VariableContrastLed {
public:
	VariableContrastLed(TIM_HandleTypeDef *timer, uint32_t channel, uint16_t contrast = 0);
	virtual ~VariableContrastLed();
	uint16_t getContrast() const;
	void setContrast(uint16_t contrast);
	void setContrastPercentage(uint8_t percentage);

private:
	TIM_HandleTypeDef *mTimer;
	uint16_t mContrast;
	uint32_t mChannel;

	void setPulseWidth(void);
};

#endif /* VARIABLECONTRASTLED_H_ */
