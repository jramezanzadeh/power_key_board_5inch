/*
 * CommandListener.cpp
 *
 *  Created on: Sep 11, 2021
 *      Author: Javad Ramezanzadeh
 */

#include "CommandListener.h"
#include "VariableContrastLed.h"
#include "Helper.h"
#include "Debug.h"
#include "string.h"
#include "i2c.h"

#define STX				0x03
#define ETX				0x02

CommandListener::CommandListener(VariableContrastLed* bgLed) {
	// TODO Auto-generated constructor stub
	mbgLed = bgLed;
	startRx();
}

CommandListener::~CommandListener() {
	// TODO Auto-generated destructor stub
}

void CommandListener::run() {
	if(HAL_I2C_GetState(&hi2c1) == HAL_I2C_STATE_READY){ // new packet has been received
//		for(int i = 0; i < I2C_RX_BUFF_LEN; i++)
//			Debug::getInstance().log("%02X ", mRxBuff[i]);
//		Debug::getInstance() << "\r\n";

		if(checkCmd()){
			Debug::getInstance() << "Valid Command\r\n";
			processCommand();
		}
		startRx(); //start receiving new commands
	}
}

void CommandListener::startRx() {
	memset(mRxBuff, 0x0, I2C_RX_BUFF_LEN);
	if(HAL_I2C_Slave_Receive_DMA(&hi2c1, mRxBuff, I2C_RX_BUFF_LEN) != HAL_OK)
		Debug::getInstance() << "I2C Start DMA failed\r\n";
}

bool CommandListener::checkCmd() {
	int offset = 0;
	mCmd.stx = mRxBuff[offset++];
	mCmd.header.cmd = mRxBuff[offset++];
	mCmd.header.len = mRxBuff[offset++];

	if(mCmd.header.len > MAX_PAYLOAD_LEN)
		return false;
	memcpy(mCmd.paylaod, mRxBuff+offset, mCmd.header.len); offset += mCmd.header.len;
	mCmd.crc = mRxBuff[offset++];
	mCmd.etx = mRxBuff[offset++];
	if(!mCmd.isValid())
		return false;
	return true;
}

void CommandListener::processCommand() {
	switch (mCmd.header.cmd) {
	case BG_BRIGHTNESS:
		cmdBgLedBrightness();
		break;
	case AIS_PWR_CTRL:
		cmdAisPowerControl();
		break;
	case GET_AIS_PWR_STATE:
		cmdGetAisPowerState();
		break;
	default:
		sendNack();
		break;
	}
}

void CommandListener::sendAck() {
}

void CommandListener::sendNack() {
}

void CommandListener::cmdBgLedBrightness() {
	if(mCmd.header.len != 1){
		sendNack();
		return;
	}
	uint8_t brightness = mCmd.paylaod[0];
	mbgLed->setContrastPercentage(brightness);
	sendAck();
}

void CommandListener::cmdAisPowerControl() {
	Debug::getInstance() << "not implemented cmd\r\n";
}

void CommandListener::cmdGetAisPowerState() {
	Debug::getInstance() << "not implemented cmd\r\n";
}

/******************************* Command Implementation *****************************/
void Command::reset() {
	stx = 0;
	memset(&header, 0, sizeof(Header));
	memset(paylaod, 0, MAX_PAYLOAD_LEN);
	crc = 0;
	etx = 0;
}

int Command::toArray(uint8_t* buff) {
	int offset = 0;
	memcpy(buff+offset, &header, sizeof(Header)); offset += sizeof(Header);
	memcpy(buff+offset, paylaod, header.len); offset += header.len;
	return offset;
}

void Command::updateCRC() {
	crc = calcCRC();
}

uint8_t Command::calcCRC() {
	uint8_t buff[50];
	int len = toArray(buff);
	return Helper::calcCRC(buff, len);
}

Command::Command() {
	stx = STX;
	etx = ETX;
	crc = 0;
}

void Command::print() {
	Debug::getInstance() << "stx: " << stx << "\r\n";
	Debug::getInstance() << "cmd: " << header.cmd << "\r\n";
	Debug::getInstance() << "len: " << header.len << "\r\n";
	Debug::getInstance() << "payload: ";
	for(int i = 0; i < header.len; i++)
		Debug::getInstance().log("%02X ", paylaod[i]);
	Debug::getInstance() << "\r\ncrc: " << crc << "\r\n";
	Debug::getInstance() << "etx: " << etx << "\r\n";
}

bool Command::checkCRC() {
	return crc == calcCRC();
}

bool Command::isValid() {
	if(stx != STX)
		return false;
	if(etx != ETX)
		return false;
	if(header.len > MAX_PAYLOAD_LEN)
		return false;
	if(!checkCRC())
		return false;
	return true;
}

