/*
 * KeyObserver.h
 *
 *  Created on: Jun 1, 2021
 *      Author: Javad Ramezanzadeh
 */

#ifndef KEYOBSERVER_H_
#define KEYOBSERVER_H_

#include "stdint.h"
enum Keys{
	Key_GOTO		= 1,
	Key_WayPoint,
	Key_Plus,
	Key_Page,
	Key_Minus,
	Key_Right,
	Key_UP,
	Key_OK,
	Key_Down,
	Key_Left,
	Key_Alt,
	Key_Menu,
	Key_Esc,
	Key_MOB,
	Key_Power
};
enum KeyEventType{
	KEY_PRESSED = 0,
	KEY_RELEASED = 1,
};

class KeyObserver {
public:
	KeyObserver();
	virtual ~KeyObserver();

	virtual void keyEvent(uint8_t keyID, KeyEventType eventType) = 0;
};

#endif /* KEYOBSERVER_H_ */
