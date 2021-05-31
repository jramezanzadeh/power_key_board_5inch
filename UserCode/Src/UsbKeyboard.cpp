/*
 * UsbKeyboard.cpp
 *
 *  Created on: May 31, 2021
 *      Author: Javad Ramezanzadeh
 */

#include "UsbKeyboard.h"

UsbKeyboard::UsbKeyboard() {
	// TODO Auto-generated constructor stub

}


UsbKeyboard::~UsbKeyboard() {
	// TODO Auto-generated destructor stub
}

void UsbKeyboard::sendMediaKey(uint8_t key) {
	MediaHID_t mediaReport;
	mediaReport.id = MEDIA_REPORT_ID;
	mediaReport.keys = key;

	//TODO handle Errors
	USBD_HID_SendReport(mUsbDevice, (uint8_t*)&mediaReport, sizeof(MediaHID_t));
}

void UsbKeyboard::sendStandardKey(uint8_t modifier, uint8_t key1, uint8_t key2,
		uint8_t key3) {
	 KeyboardHID_t keyReport;
	 keyReport.id = KEYBOARD_REPORT_ID;
	 keyReport.modifiers = modifier;
	 keyReport.key1 = key1;
	 keyReport.key2 = key2;
	 keyReport.key3 = key3;

	 //TODO handle Errors
	 USBD_HID_SendReport(mUsbDevice, (uint8_t*)&keyReport, sizeof(KeyboardHID_t));
}

void UsbKeyboard::releaseMediaKey() {
	sendMediaKey(0);
}

void UsbKeyboard::releaseStandardKey() {
	sendStandardKey(0,0,0,0);
}

void UsbKeyboard::releaseAllKey() {
	releaseMediaKey();
	releaseStandardKey();
}

UsbKeyboard UsbKeyboard::instance() {
	static UsbKeyboard keyboard;
	return keyboard;
}

void UsbKeyboard::init(USBD_HandleTypeDef* usbDevice) {
	mUsbDevice = usbDevice;
}
