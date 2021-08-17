/*
 * UsbKeyboard.cpp
 *
 *  Created on: May 31, 2021
 *      Author: Javad Ramezanzadeh
 */

#include "UsbKeyboard.h"
#include "Debug.h"

UsbKeyboard::UsbKeyboard() {
	// TODO Auto-generated constructor stub
	mUsbDevice = 0;
	mReadIndex = 0;
	mWriteIndex = 0;
	mState = IDLE;
	mPollingInterval = 0;
	mStartPollingTime = 0;


	mKeysMap[Key_GOTO] 		= USB_HID_KEY_F8; 		//Goto/Find
	mKeysMap[Key_WayPoint] 	= USB_HID_KEY_F9;		// WP/Mark
	mKeysMap[Key_Plus] 		= USB_HID_KEYPAD_PLUS;	//+
	mKeysMap[Key_Page] 		= USB_HID_KEY_PAGE_DOWN;//page
	mKeysMap[Key_Minus] 	= USB_HID_KEYPAD_MINUS; //-
	mKeysMap[Key_Right] 	= USB_HID_KEY_RIGHT;	//>
	mKeysMap[Key_UP] 		= USB_HID_KEY_UP;		// /\(up)
	mKeysMap[Key_OK] 		= USB_HID_KEY_F10;		//OK
	mKeysMap[Key_Down] 		= USB_HID_KEY_DOWN;		// \/(down)
	mKeysMap[Key_Left] 		= USB_HID_KEY_LEFT;		//<
	mKeysMap[Key_Alt] 		= USB_HID_KEY_F2; 		//ALT
	mKeysMap[Key_Menu] 		= USB_HID_KEYPAD_ENTER; //menu
	mKeysMap[Key_Esc] 		= USB_HID_KEY_ESC;		//ESP
	mKeysMap[Key_MOB] 		= USB_HID_KEY_F7;		//MOB
	mKeysMap[Key_Power] 	= USB_HID_KEY_F6;		//Power

}


UsbKeyboard::~UsbKeyboard() {
	// TODO Auto-generated destructor stub
}

void UsbKeyboard::sendMediaKey(uint8_t key) {

	mediaReport.id = MEDIA_REPORT_ID;
	mediaReport.keys = key;

	sendBuff((uint8_t*)&mediaReport, sizeof(MediaHID_t));
}

void UsbKeyboard::sendStandardKey(uint8_t modifier, uint8_t key1, uint8_t key2,
		uint8_t key3) {
	keyReport.id = KEYBOARD_REPORT_ID;
	keyReport.modifiers = modifier;
	keyReport.key1 = key1;
	keyReport.key2 = key2;
	keyReport.key3 = key3;

	sendBuff((uint8_t*)&keyReport, sizeof(KeyboardHID_t));
}

void UsbKeyboard::releaseMediaKey() {
	sendMediaKey(0);
}

void UsbKeyboard::releaseStandardKey() {
	sendStandardKey(0,0,0,0);
}

void UsbKeyboard::releaseAllKey() {
	releaseMediaKey();
	HAL_Delay(mPollingInterval);
	releaseStandardKey();
}

UsbKeyboard& UsbKeyboard::instance() {
	static UsbKeyboard keyboard;
	return keyboard;
}

void UsbKeyboard::init(USBD_HandleTypeDef* usbDevice) {
	if(!usbDevice)
		return;
	mUsbDevice = usbDevice;
	mPollingInterval = USBD_HID_GetPollingInterval(mUsbDevice);

}

void UsbKeyboard::handleKeyEvent(int keyId, KeyEventType eventType) {
	// save event
	mEventList[mWriteIndex].keyId = keyId;
	mEventList[mWriteIndex].type = eventType;
	mWriteIndex += 1;
	mWriteIndex %= BUFF_SIZE;
}

void UsbKeyboard::run(void) {
	//TODO: return if it isn't initialized correctly
	switch (mState) {
		case IDLE:
			if(isEventExist())
				handleBufferedKey();
			break;
		case WAIT_POLLING_INTERVAL:
			if(isPollingTimeElapsed())
				mState = IDLE;
			break;
		default:
			break;
	}
}

void UsbKeyboard::sendStandardKey(KeyboardHID_t* key) {
	sendBuff((uint8_t*)key, sizeof(KeyboardHID_t));
}

bool UsbKeyboard::isEventExist() {
	return mWriteIndex != mReadIndex;
}

void UsbKeyboard::notify() {
	for(int i = 0; i < (int)mObserverList.size(); i++)
		mObserverList[i]->keyEvent(mEventList[mReadIndex].keyId, mEventList[mReadIndex].type);
}

void UsbKeyboard::sendBuff(uint8_t* buff, int len) {

	//TODO handle Errors
	USBD_HID_SendReport(mUsbDevice, buff, len);
	mState = WAIT_POLLING_INTERVAL;
	mStartPollingTime = HAL_GetTick();
}

void UsbKeyboard::handleBufferedKey() {
	switch (mEventList[mReadIndex].type) {
	case KEY_PRESSED:
		sendStandardKey(0, mKeysMap[mEventList[mReadIndex].keyId]);
		Debug::getInstance().log("press key[%d]\r\n", mEventList[mReadIndex].keyId);
		break;
	case KEY_RELEASED:
		releaseStandardKey();
		Debug::getInstance().log("release key[%d]\r\n", mEventList[mReadIndex].keyId);
		break;
	default:
		Debug::getInstance() << "unhandled\r\n";
		break;
	}
	notify();
	mReadIndex++;
	mReadIndex %= BUFF_SIZE;
}

bool UsbKeyboard::isPollingTimeElapsed() {
	return (HAL_GetTick() - mStartPollingTime > mPollingInterval);
}
