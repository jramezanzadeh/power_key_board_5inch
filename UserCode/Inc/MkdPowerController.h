/*
 * MkdPowerController.h
 *
 *  Created on: Jun 1, 2021
 *      Author: Javad Ramezanzadeh
 */

#ifndef MKDPOWERCONTROLLER_H_
#define MKDPOWERCONTROLLER_H_

#include <KeyObserver.h>
#include <StateObserver.h>
#include "GpioHandler.h"
#include "VariableContrastLed.h"

enum MkdPowerState{
	ON		= 0,
	OFF	= 1,
};

class MkdPowerController: public StateObserver, public KeyObserver {
public:
	MkdPowerController(GpioHandler* pwr3V3Ctrl, GpioHandler* pwr5VCtrl,
			VariableContrastLed* ledPower, VariableContrastLed* bgLed);
	virtual ~MkdPowerController();

	void run();
	void stateChanged(PowerState state);
	void keyEvent(uint8_t keyID, KeyEventType eventType);

	MkdPowerState getPowerState() const {
		return mPowerState;
	}

private:

	MkdPowerState 			mPowerState;
	GpioHandler* 			mPwr3V3Ctrl;
	GpioHandler* 			mPwr5VCtrl;
	VariableContrastLed* 	mLedPower;
	VariableContrastLed* 	mBgLed;
	bool					mIsInputPwrPresent;
	bool					mIsPowerKeyPressed;
	uint32_t				mKeyPressedTime;
	uint32_t				mLastIncreasingContrastTime;
	uint8_t					mLedContrastPercentage;

	void mkdPowerOn();
	void mkdPowerOff();
};

#endif /* MKDPOWERCONTROLLER_H_ */
