/*
 * CommandListener.h
 *
 *  Created on: Sep 11, 2021
 *      Author: Javad Ramezanzadeh
 */

#ifndef COMMANDLISTENER_H_
#define COMMANDLISTENER_H_

#include "stdint.h"

#define I2C_RX_BUFF_LEN		20
#define MAX_PAYLOAD_LEN		10

class Header{
public:
	uint8_t cmd; // command
	uint8_t len; //payload len
};

class Command{
public:
	uint8_t 	stx;
	Header 		header;
	uint8_t 	paylaod[MAX_PAYLOAD_LEN];
	uint8_t		crc;
	uint8_t		etx;
	Command();
	bool isValid();
	void reset();
	void updateCRC();
	void print();
	int toArray(uint8_t *buff);
private:
	uint8_t calcCRC();
	bool checkCRC();
};

class VariableContrastLed;
class CommandListener {
public:
	CommandListener(VariableContrastLed* bgLed);
	virtual ~CommandListener();

	void run();

private:
	enum Commands{
		ACK = 1,
		NACK,
		BG_BRIGHTNESS,
		AIS_PWR_CTRL,
		GET_AIS_PWR_STATE,
		GET_AIS_PWR_STATE_RESP,
	};
	VariableContrastLed* mbgLed;
	uint8_t	mRxBuff[I2C_RX_BUFF_LEN];
	Command	mCmd;

	void startRx();
	bool checkCmd();
	void processCommand();
	void sendAck();
	void sendNack();
	void cmdBgLedBrightness();
	void cmdAisPowerControl();
	void cmdGetAisPowerState();
};

#endif /* COMMANDLISTENER_H_ */
