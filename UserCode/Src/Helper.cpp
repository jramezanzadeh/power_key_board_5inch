/*
 * Helper.cpp
 *
 *  Created on: Apr 26, 2021
 *      Author: Javad Ramezanzadeh
 */

#include <Helper.h>

Helper::Helper() {
	// TODO Auto-generated constructor stub

}

Helper::~Helper() {
	// TODO Auto-generated destructor stub
}

void Helper::toBigEndianArray(uint8_t* buff, uint32_t val) {
	buff[0] = (uint8_t)(val >> 24);
	buff[1] = (uint8_t)(val >> 16);
	buff[2] = (uint8_t)(val >> 8);
	buff[3] = (uint8_t)(val);
}

void Helper::toBigEndianArray(uint8_t* buff, uint16_t val) {
	buff[0] = (uint8_t)(val >> 8); //MSB first
	buff[1] = (uint8_t)(val);
}

uint32_t Helper::fromBigEndianArray(uint8_t* buff, int len) {
	uint32_t data = 0;
	if(len > 4) return data;
	for(int i = 0; i < len; i++){
		data <<= 8;
		data += buff[i];
	}
	return data;
}

//uint16_t Helper::fromBigEndianArray(uint8_t* buff) {
//	uint16_t data;
//	data  = (uint16_t)buff[0] << 8;
//	data += (uint16_t)buff[1];
//	return data;
//}
