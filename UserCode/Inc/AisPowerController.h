/*
 * AisPowerController.h
 *
 *  Created on: Jun 1, 2021
 *      Author: Javad Ramezanzadeh
 */

#ifndef AISPOWERCONTROLLER_H_
#define AISPOWERCONTROLLER_H_

#include <StateObserver.h>
#include "GpioHandler.h"

class AisPowerController: public StateObserver {
public:
	AisPowerController(GpioHandler* inputPwrCtrlPin,
			GpioHandler* ais3V8PwrCtrlPin);
	virtual ~AisPowerController();

	void stateChanged(PowerState state);
private:
	GpioHandler* mInputPwrCtrlPin;
	GpioHandler* mAis3V8PwrCtrlPin;

};

#endif /* AISPOWERCONTROLLER_H_ */
