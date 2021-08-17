/*
 * UsbKeyboard.h
 *
 *  Created on: May 31, 2021
 *      Author: Javad Ramezanzadeh
 */

#ifndef USBKEYBOARD_H_
#define USBKEYBOARD_H_

#include "usbd_hid.h"
#include "stdint.h"
#include "map"
#include "Observable.h"
#include "KeyObserver.h"

#define BUFF_SIZE 5

class UsbKeyboard: public Observable<KeyObserver> {
public:
	// USB media codes
	enum UsbMediaCodes{
		USB_HID_SCAN_NEXT  = 0x01,
		USB_HID_SCAN_PREV  = 0x02,
		USB_HID_STOP       = 0x04,
		USB_HID_EJECT      = 0x08,
		USB_HID_PAUSE      = 0x10,
		USB_HID_MUTE       = 0x20,
		USB_HID_VOL_UP     = 0x40,
		USB_HID_VOL_DEC    = 0x80
	};

	// USB USB_HID_KEYboard codes
	enum KeyboardModifiers{
		USB_HID_MODIFIER_LEFT_CTRL   = 0x01,
		USB_HID_MODIFIER_LEFT_SHIFT  = 0x02,
		USB_HID_MODIFIER_LEFT_ALT    = 0x04,
		USB_HID_MODIFIER_LEFT_GUI    = 0x08, // (Win/Apple/Meta)
		USB_HID_MODIFIER_RIGHT_CTRL  = 0x10,
		USB_HID_MODIFIER_RIGHT_SHIFT = 0x20,
		USB_HID_MODIFIER_RIGHT_ALT   = 0x40,
		USB_HID_MODIFIER_RIGHT_GUI   = 0x80,
	};

	enum KeyboardCodes{
		USB_HID_KEY_A    			= 0x04,
		USB_HID_KEY_B    			= 0x05,
		USB_HID_KEY_C    			= 0x06,
		USB_HID_KEY_D    			= 0x07,
		USB_HID_KEY_E    			= 0x08,
		USB_HID_KEY_F    			= 0x09,
		USB_HID_KEY_G    			= 0x0A,
		USB_HID_KEY_H    			= 0x0B,
		USB_HID_KEY_I    			= 0x0C,
		USB_HID_KEY_J    			= 0x0D,
		USB_HID_KEY_K    			= 0x0E,
		USB_HID_KEY_L    			= 0x0F,
		USB_HID_KEY_M    			= 0x10,
		USB_HID_KEY_N    			= 0x11,
		USB_HID_KEY_O    			= 0x12,
		USB_HID_KEY_P    			= 0x13,
		USB_HID_KEY_Q    			= 0x14,
		USB_HID_KEY_R    			= 0x15,
		USB_HID_KEY_S    			= 0x16,
		USB_HID_KEY_T    			= 0x17,
		USB_HID_KEY_U    			= 0x18,
		USB_HID_KEY_V    			= 0x19,
		USB_HID_KEY_W    			= 0x1A,
		USB_HID_KEY_X    			= 0x1B,
		USB_HID_KEY_Y    			= 0x1C,
		USB_HID_KEY_Z    			= 0x1D,
		USB_HID_KEY_1    			= 0x1E,
		USB_HID_KEY_2    			= 0x1F,
		USB_HID_KEY_3    			= 0x20,
		USB_HID_KEY_4    			= 0x21,
		USB_HID_KEY_5    			= 0x22,
		USB_HID_KEY_6    			= 0x23,
		USB_HID_KEY_7    			= 0x24,
		USB_HID_KEY_8    			= 0x25,
		USB_HID_KEY_9    			= 0x26,
		USB_HID_KEY_0    			= 0x27,
		USB_HID_KEY_ENTER    		= 0x28,
		USB_HID_KEY_ESC    			= 0x29,
		USB_HID_KEY_BACKSPACE    	= 0x2A,
		USB_HID_KEY_TAB    			= 0x2B,
		USB_HID_KEY_SPACE    		= 0x2C,
		USB_HID_KEY_MINUS    		= 0x2D,
		USB_HID_KEY_EQUAL    		= 0x2E,
		USB_HID_KEY_LEFT_BRACE    	= 0x2F,
		USB_HID_KEY_RIGHT_BRACE    	= 0x30,
		USB_HID_KEY_BACKSLASH    	= 0x31,
		USB_HID_KEY_NUMBER    		= 0x32,
		USB_HID_KEY_SEMICOLON    	= 0x33,
		USB_HID_KEY_QUOTE    		= 0x34,
		USB_HID_KEY_TILDE    		= 0x35,
		USB_HID_KEY_COMMA    		= 0x36,
		USB_HID_KEY_PERIOD    		= 0x37,
		USB_HID_KEY_SLASH    		= 0x38,
		USB_HID_KEY_CAPS_LOCK    	= 0x39,
		USB_HID_KEY_F1    			= 0x3A,
		USB_HID_KEY_F2    			= 0x3B,
		USB_HID_KEY_F3    			= 0x3C,
		USB_HID_KEY_F4    			= 0x3D,
		USB_HID_KEY_F5    			= 0x3E,
		USB_HID_KEY_F6    			= 0x3F,
		USB_HID_KEY_F7    			= 0x40,
		USB_HID_KEY_F8    			= 0x41,
		USB_HID_KEY_F9    			= 0x42,
		USB_HID_KEY_F10   			= 0x43,
		USB_HID_KEY_F11   			= 0x44,
		USB_HID_KEY_F12   			= 0x45,
		USB_HID_KEY_PRINTSCREEN    	= 0x46,
		USB_HID_KEY_SCROLL_LOCK    	= 0x47,
		USB_HID_KEY_PAUSE    		= 0x48,
		USB_HID_KEY_INSERT    		= 0x49,
		USB_HID_KEY_HOME    		= 0x4A,
		USB_HID_KEY_PAGE_UP    		= 0x4B,
		USB_HID_KEY_DELETE    		= 0x4C,
		USB_HID_KEY_END    			= 0x4D,
		USB_HID_KEY_PAGE_DOWN    	= 0x4E,
		USB_HID_KEY_RIGHT    		= 0x4F,
		USB_HID_KEY_LEFT    		= 0x50,
		USB_HID_KEY_DOWN    		= 0x51,
		USB_HID_KEY_UP    			= 0x52,
		USB_HID_KEY_NUM_LOCK    	= 0x53,
		USB_HID_KEYPAD_SLASH    	= 0x54,
		USB_HID_KEYPAD_ASTERIX    	= 0x55,
		USB_HID_KEYPAD_MINUS    	= 0x56,
		USB_HID_KEYPAD_PLUS    		= 0x57,
		USB_HID_KEYPAD_ENTER    	= 0x58,
		USB_HID_KEYPAD_1    		= 0x59,
		USB_HID_KEYPAD_2    		= 0x5A,
		USB_HID_KEYPAD_3    		= 0x5B,
		USB_HID_KEYPAD_4    		= 0x5C,
		USB_HID_KEYPAD_5    		= 0x5D,
		USB_HID_KEYPAD_6    		= 0x5E,
		USB_HID_KEYPAD_7    		= 0x5F,
		USB_HID_KEYPAD_8    		= 0x60,
		USB_HID_KEYPAD_9    		= 0x61,
		USB_HID_KEYPAD_0    		= 0x62,
		USB_HID_KEYPAD_PERIOD    	= 0x63,
	};

	virtual ~UsbKeyboard();
	static UsbKeyboard& instance();
	void init(USBD_HandleTypeDef* usbDevice);
	void handleKeyEvent(int keyId, KeyEventType eventType);
	void run(void);


private:
	enum State{
		IDLE = 0,
		WAIT_POLLING_INTERVAL
	};
	enum{
		KEYBOARD_REPORT_ID	= 1,
		MEDIA_REPORT_ID		= 2,
	};
	typedef struct  {
		uint8_t id;
		uint8_t keys;
	}__attribute__((packed)) MediaHID_t;

	// HID Keyboard
	typedef struct  {
		uint8_t id;
		uint8_t modifiers;
		uint8_t key1;
		uint8_t key2;
		uint8_t key3;
	}__attribute__((packed)) KeyboardHID_t;

	typedef struct{
		uint8_t 		keyId;
		KeyEventType	type;
	}event_t;

	KeyboardHID_t 						keyReport;
	MediaHID_t 							mediaReport;
	USBD_HandleTypeDef* 				mUsbDevice;
	std::map<uint8_t, uint8_t> 			mKeysMap;
	event_t								mEventList[BUFF_SIZE];
	int									mReadIndex;
	volatile int						mWriteIndex;
	uint32_t							mPollingInterval;
	uint32_t							mStartPollingTime;
	State								mState;

	UsbKeyboard();
	void sendMediaKey(uint8_t key);
	void sendStandardKey(uint8_t modifier, uint8_t key1, uint8_t key2 = 0, uint8_t key3 = 0);
	void sendStandardKey(KeyboardHID_t *key);
	void releaseMediaKey();
	void releaseStandardKey();
	void releaseAllKey();
	bool isEventExist();
	void notify();
	void sendBuff(uint8_t*buff, int len);
	void handleBufferedKey();
	bool isPollingTimeElapsed();

};

#endif /* USBKEYBOARD_H_ */
