/*
 * Observable.h
 *
 *  Created on: Jun 1, 2021
 *      Author: Javad Ramezanzadeh
 */

#ifndef OBSERVABLE_H_
#define OBSERVABLE_H_

//#include "Observer.h"
#include "vector"
#include<bits/stdc++.h>

template<class T>

class Observable {
public:
	Observable();
	virtual ~Observable();

	virtual void addObserver(T& observer);
	virtual void removeObserver(T& observer);

protected:
	virtual void notify() = 0;
	std::vector<T*> mObserverList;

};

template<class T>
inline Observable<T>::Observable() {
}

template<class T>
inline Observable<T>::~Observable() {
}

template<class T>
inline void Observable<T>::addObserver(T& observer) {
	mObserverList.push_back(&observer);
	notify(); // let new observer know what the state is.
}

template<class T>
inline void Observable<T>::removeObserver(T& observer) {
	std::remove(mObserverList.begin(), mObserverList.end(), &observer);
}
#endif /* OBSERVABLE_H_ */
