/*
 * PowerStateMonitor.cpp
 *
 *  Created on: Jun 1, 2021
 *      Author: Javad Ramezanzadeh
 */

#include "PowerStateMonitor.h"
#include "Debug.h"

PowerStateMonitor::PowerStateMonitor(GpioHandler *plugInPin,
		GpioHandler* mode0, GpioHandler* mode1) {
	// TODO Auto-generated constructor stub
	mPlugInPin = plugInPin;
	mMode0 = mode0;
	mMode1 = mode1;
	lastPinValue = mPlugInPin->read();
	updatePowerState();
}

PowerStateMonitor::~PowerStateMonitor() {
	// TODO Auto-generated destructor stub
}

void PowerStateMonitor::run() {

	if(mPlugInPin->read() != lastPinValue){
		lastPinValue = mPlugInPin->read();
		updatePowerState();
		notify();
	}
}

void PowerStateMonitor::notify() {
	for(int i = 0; i < (int)mObserverList.size(); i++)
		mObserverList[i]->stateChanged(powerState);
}

void PowerStateMonitor::updatePowerState() {
	//TODO add Battery state too, it is supposed that battery always is present
	powerState = lastPinValue? POWER_ON_BOTH:POWER_ON_BATT;
	Debug::getInstance().log("PowerState changed --> %d\r\n", powerState);
	switch(powerState){
	case POWER_DOWN:
		mMode0->setLow();
		mMode1->setLow();
		break;
	case POWER_ON_BATT:
		mMode0->setHigh();
		mMode1->setLow();
		break;
	case POWER_ON_INPUT:
		mMode0->setLow();
		mMode1->setHigh();
		break;
	case POWER_ON_BOTH:
		mMode0->setHigh();
		mMode1->setHigh();
		break;

	}
}
