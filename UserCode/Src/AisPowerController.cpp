/*
 * AisPowerController.cpp
 *
 *  Created on: Jun 1, 2021
 *      Author: Javad Ramezanzadeh
 */

#include "AisPowerController.h"
#include "Debug.h"

AisPowerController::AisPowerController(GpioHandler* inputPwrCtrlPin,
		GpioHandler* ais3V8PwrCtrlPin) {
	mInputPwrCtrlPin = inputPwrCtrlPin;
	mAis3V8PwrCtrlPin = ais3V8PwrCtrlPin;
}

AisPowerController::~AisPowerController() {
	// TODO Auto-generated destructor stub
}

void AisPowerController::stateChanged(PowerState state) {
	Debug::getInstance() << "AisPowerController handle satate change -->" << state << "\r\n";
	switch (state) {
	case POWER_DOWN:
		//Actually this state never happen
		mInputPwrCtrlPin->setLow();
		mAis3V8PwrCtrlPin->setLow();
		break;
	case POWER_ON_BATT: //only battery is present.
		mInputPwrCtrlPin->setLow();
		mAis3V8PwrCtrlPin->setHigh();
		break;
	case POWER_ON_INPUT: // input power is present
	case POWER_ON_BOTH:
		mInputPwrCtrlPin->setHigh();
		mAis3V8PwrCtrlPin->setLow();
		break;
	default:
		mInputPwrCtrlPin->setLow();
		mAis3V8PwrCtrlPin->setLow();
		break;
	}
}

