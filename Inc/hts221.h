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

#define HTS221_ADDRESS    0xBE
#define WHO_AM_I          0x0F
#define AV_CONF           0x10
#define CTRL_REG1         0x20
#define CTRL_REG2         0x21
#define CTRL_REG3         0x23
#define STATUS_REG        0x27
#define HUMIDITY_OUT_L    0x28
#define HUMIDITY_OUT_H    0x29
#define TEMP_OUT_L        0x2A
#define TEMP_OUT_H        0x2B

#define CTRL_REG1_PD      0x80
#define CTRL_REG1_BDU     0x04
#define CTRL_REG1_ODR     0x03


uint8_t readMemI2C (uint16_t DevAddress, uint8_t MemAddress);
HAL_StatusTypeDef writeMemI2C (uint16_t DevAddress, uint8_t MemAddress, uint8_t value);
void initHTS221(void (*transfer)(uint8_t *str, size_t size));

#endif /* INC_HTS221_H_ */
