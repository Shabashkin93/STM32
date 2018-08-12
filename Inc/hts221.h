/*
 * hts221.h
 *
 *  Created on: Aug 9, 2018
 *      Author: oleg
 */

#ifndef INC_HTS221_H_
#define INC_HTS221_H_

#include "stm32f7xx_hal.h"
#include <inttypes.h>
#include "i2c.h"
#include "usart.h"
#include "console.h"

#define        HTS221_ADDRESS        0xBE

void testTHS221(void (*transfer)(char *str, size_t size));

#endif /* INC_HTS221_H_ */
