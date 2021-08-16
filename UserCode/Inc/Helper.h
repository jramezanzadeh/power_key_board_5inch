/*
 * Helper.h
 *
 *  Created on: Apr 26, 2021
 *      Author: Javad Ramezanzadeh
 */

#ifndef HELPER_H_
#define HELPER_H_

#include "stdint.h"

class Helper {
public:
	Helper();
	virtual ~Helper();

	static void toBigEndianArray(uint8_t *buff, uint32_t val);
	static void toBigEndianArray(uint8_t *buff, uint16_t val);
	static uint32_t fromBigEndianArray(uint8_t *buff, int len);
};

#endif /* HELPER_H_ */
