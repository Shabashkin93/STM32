/*
 * hts221.c
 *
 *  Created on: Aug 10, 2018
 *      Author: oleg
 */

#include "hts221.h"

I2C_HandleTypeDef hi2c2;
uint8_t datai2c[3] = {'\n', 0, 0};
uint8_t i2cReady[17]="hts221 is ready\n\r";

uint8_t readMemI2C (uint16_t DevAddress,uint8_t MemAddress){
    uint8_t result = 0;
    HAL_I2C_Mem_Read(&hi2c2, DevAddress, MemAddress, 1, (uint8_t*) &result, 1, 1000);
    return (result);
}

HAL_StatusTypeDef writeMemI2C (uint16_t DevAddress, uint8_t MemAddress, uint8_t value){
  return (HAL_I2C_Mem_Write(&hi2c2, DevAddress, MemAddress, 1, (uint8_t*) &value, 1, 1000));
}

void initHTS221(void (*transfer)(uint8_t *str, size_t size)){
	if(HAL_I2C_IsDeviceReady (&hi2c2, HTS221_ADDRESS, 1, 1000) == HAL_OK){
	  transfer((uint8_t*) &i2cReady,17);
	}
	uint8_t bufTransfer=0;
	bufTransfer = readMemI2C(HTS221_ADDRESS, WHO_AM_I);
	transfer((uint8_t*) &bufTransfer, 1);
	bufTransfer = readMemI2C(HTS221_ADDRESS, TEMP_OUT_L);
	transfer((uint8_t*) &bufTransfer, 1);
	bufTransfer = readMemI2C(HTS221_ADDRESS, TEMP_OUT_H);
	transfer((uint8_t*) &bufTransfer, 1);
	uint8_t memValue;
	memValue = readMemI2C(HTS221_ADDRESS, CTRL_REG1);
	memValue &=~ CTRL_REG1_PD;
	writeMemI2C(HTS221_ADDRESS, CTRL_REG1, memValue);
}
