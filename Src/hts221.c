/*
 * hts221.c
 *
 *  Created on: Aug 10, 2018
 *      Author: oleg
 */

#include "hts221.h"

I2C_HandleTypeDef hi2c2;
uint8_t datai2c[2] = {'\n',0};
uint8_t i2cReady[17]="hts221 is ready\n\r";


void testTHS221(void (*transfer)(char *str, size_t size)){ /* Test ready Hts221*/
	if(HAL_I2C_IsDeviceReady (&hi2c2, HTS221_ADDRESS, 1, 1000) == HAL_OK){
	  transfer(i2cReady,17);
	}
	if(HAL_I2C_Mem_Read(&hi2c2, HTS221_ADDRESS, 0x0F, 1, datai2c, 1, 1000) == HAL_OK){
	    transfer(datai2c,2);
	}
}
