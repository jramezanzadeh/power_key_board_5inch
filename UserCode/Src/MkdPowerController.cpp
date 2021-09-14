/*
 * MkdPowerController.cpp
 *
 *  Created on: Jun 1, 2021
 *      Author: Javad Ramezanzadeh
 */

#include "MkdPowerController.h"

MkdPowerController::MkdPowerController(GpioHandler* pwr3V3Ctrl,
		GpioHandler* pwr5VCtrl, VariableContrastLed* ledPower,
		VariableContrastLed* bgLed) {
	// TODO Auto-generated constructor stub
	mPwr3V3Ctrl = pwr3V3Ctrl;
	mPwr5VCtrl = pwr5VCtrl;
	mLedPower = ledPower;
	mBgLed = bgLed;
	mPowerState = OFF;
	mIsInputPwrPresent = false;
	mIsPowerKeyPressed = false;
	mKeyPressedTime = 0;
	mLastIncreasingContrastTime = 0;
	mLedContrastPercentage = 0;
	mkdPowerOff();
}

MkdPowerController::~MkdPowerController() {
	// TODO Auto-generated destructor stub
}

void MkdPowerController::stateChanged(PowerState state) {
	switch (state) {
	case POWER_DOWN:
	case POWER_ON_BATT:
		mIsPowerKeyPressed = false;
		mIsInputPwrPresent = false;
		mkdPowerOff();
		break;
	case POWER_ON_INPUT:
	case POWER_ON_BOTH:
		mLedContrastPercentage = 0;
		mLastIncreasingContrastTime = HAL_GetTick();
		mIsInputPwrPresent = true;
		break;
	}
}

void MkdPowerController::keyEvent(uint8_t keyID, KeyEventType eventType) {
	if(mIsInputPwrPresent){
		if(keyID == Key_Power){
			if(eventType == KEY_PRESSED){
				mKeyPressedTime = HAL_GetTick(); // capture event time
				mIsPowerKeyPressed = true;
			}else{
				mIsPowerKeyPressed = false;
			}
		}
	}
}

void MkdPowerController::run() {
	// handle power key press
	if(mIsPowerKeyPressed){
		if(mPowerState == ON){
			if(HAL_GetTick() - mKeyPressedTime > 3000){ // check whether press time is more than 3 seconds or not
				mIsPowerKeyPressed = false;
				mkdPowerOff();
			}
		}else{
			// power on MKD immediately
			mIsPowerKeyPressed = false;
			mkdPowerOn();
		}
	}
	//handle periodically increasing power led's contrast
	//TODO write it in a clear way
	if(mIsInputPwrPresent && (mPowerState == OFF)){
		if(HAL_GetTick() - mLastIncreasingContrastTime > 500){
			mLastIncreasingContrastTime = HAL_GetTick();
			mLedContrastPercentage += 10;
			mLedContrastPercentage %= 101;
			mLedPower->setContrastPercentage(mLedContrastPercentage);
		}
	}
}

void MkdPowerController::mkdPowerOn() {
	mPowerState = ON;
	mPwr3V3Ctrl->setHigh();
	mPwr5VCtrl->setHigh();

	mLedContrastPercentage = 100;
	mLedPower->setContrastPercentage(mLedContrastPercentage);
	//HAL_Delay(100); //TODO when the mkd is turned on, 5V power will oscillate(why???)

}

void MkdPowerController::mkdPowerOff() {
	mPowerState = OFF;
	mPwr3V3Ctrl->setLow();
	mPwr5VCtrl->setLow();

	mLedContrastPercentage = 0;
	mLedPower->setContrastPercentage(mLedContrastPercentage);
	mLastIncreasingContrastTime = HAL_GetTick();
	mBgLed->setContrastPercentage(0);

}
