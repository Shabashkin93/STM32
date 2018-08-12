#ifndef __DAC_SET_H                                                                                              

#define __DAC_SET_H

#include <inttypes.h>
#include "math.h"
#include "stm32f7xx_hal.h"

#define AMOUNT_OF_POINTS 2500

void DACSet();
void DACStart();
void DACStop();

#endif /* __DAC_SET_H */  
