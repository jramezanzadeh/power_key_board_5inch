/*
 * Observer.h
 *
 *  Created on: Jun 1, 2021
 *      Author: Javad Ramezanzadeh
 */

#ifndef OBSERVER_H_
#define OBSERVER_H_

typedef enum{
	POWER_DOWN		= 0, /*mode0 = 0, mode1 = 0, neither battery nor input are present*/
	POWER_ON_BATT	= 1, /*mode0 = 1, mode1 = 0, only battery is present*/
	POWER_ON_INPUT	= 2, /*mode0 = 0, mode1 = 1, only input is present*/
	POWER_ON_BOTH	= 3, /*mode0 = 1, mode1 = 1, both battery and input are preset*/
}PowerState;

class StateObserver {
public:

	StateObserver();
	virtual ~StateObserver();

	virtual void stateChanged(PowerState state) = 0;
};

#endif /* OBSERVER_H_ */
