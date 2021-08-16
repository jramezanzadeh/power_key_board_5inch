/*
 * PowerStateMonitor.h
 *
 *  Created on: Jun 1, 2021
 *      Author: Javad Ramezanzadeh
 */

#ifndef POWERSTATEMONITOR_H_
#define POWERSTATEMONITOR_H_

#include <Observable.h>
#include "StateObserver.h"
#include "GpioHandler.h"

class PowerStateMonitor: public Observable<StateObserver> {
public:
	PowerStateMonitor(GpioHandler *plugInPin,
			GpioHandler* mode0, GpioHandler* mode1);
	virtual ~PowerStateMonitor();

	void run();

	PowerState getPowerState() const {
		return powerState;
	}


private:
	GpioHandler* 			mPlugInPin;
	GpioHandler* 			mMode0;
	GpioHandler* 			mMode1;
	bool 					lastPinValue;
	PowerState powerState;

	void notify();
	void updatePowerState();

};

#endif /* POWERSTATEMONITOR_H_ */
