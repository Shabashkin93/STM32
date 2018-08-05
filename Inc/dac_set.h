#ifndef __DAC_SET_H                                                                                              

#define __DAC_SET_H

#include <inttypes.h>
#include "math.h"
#include "stm32f7xx_hal.h"

#define AMOUNT_OF_POINTS 2500

static uint16_t sine[AMOUNT_OF_POINTS * 4];

void dac_set();
void dac_start();
void dac_stop();

#endif /* __DAC_SET_H */  
