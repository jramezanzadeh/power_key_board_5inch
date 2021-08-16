/*
 * Debug.cpp
 *
 *  Created on: Apr 25, 2021
 *      Author: Javad Ramezanzadeh
 */

#include <Debug.h>
#include <cstdarg>
#include <stdio.h>
#include <stdlib.h>
#include "string.h"

Debug& Debug::getInstance() {
	static Debug debuger;
	return debuger;
}

Debug& Debug::operator <<(int num) {
	char tmpStr[20];
	sprintf(tmpStr, " %d", num);
	debugPort.send((uint8_t*)tmpStr, strlen(tmpStr));
	return *this;
}

Debug& Debug::operator <<(const char* str) {
	debugPort.send((uint8_t*)str, strlen(str));
	return *this;
}

void Debug::log(const char* fmt...) {
	char tmpStr[100];
	va_list args;
	va_start(args, fmt);
	int RetLen = vsnprintf(tmpStr, 100, fmt, args);
	if(RetLen < 100)
		debugPort.send((uint8_t*)tmpStr, RetLen, 200);
	else{
		operator <<("error in writing log\r\n");
	}
	va_end(args);
}

Debug::Debug():debugPort(DBG_HANDLER_PTR) {
	// TODO Auto-generated constructor stub
	debugPort.init(DBG_UART_PTR, 115200, UART_MODE_TX);
	debugPort.open();
}

Debug::~Debug() {
	// TODO Auto-generated destructor stub
}

