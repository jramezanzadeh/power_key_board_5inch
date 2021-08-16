/*
 * Debug.h
 *
 *  Created on: Apr 25, 2021
 *      Author: Javad Ramezanzadeh
 */

#ifndef DEBUG_H_
#define DEBUG_H_

#include "Serial.hpp"

#define DBG_PORT_NUM 5

#define _HANDLER_PTR_(n)		&huart##n
#define HANDLER_PTR_(n)			_HANDLER_PTR_(n)

#define _UART_PTR_(n)  			UART##n
#define  UART_PTR_(n) 			_UART_PTR_(n)

#define DBG_HANDLER_PTR			(HANDLER_PTR_(DBG_PORT_NUM))
#define DBG_UART_PTR			(UART_PTR_(DBG_PORT_NUM))


class Debug {
public:
	static Debug& getInstance();
	virtual ~Debug();

	Debug& operator << (int num);
	Debug& operator << (const char *str);
	void log(const char *fmt...);
private:
	Debug();
	Serial debugPort;
};

#endif /* DEBUG_H_ */
