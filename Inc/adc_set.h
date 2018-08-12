#ifndef __ADC_SET_H
#define __ADC_SET_H

#include <inttypes.h>
#include "stm32f7xx_hal.h"
#include "console.h"
#include <string.h>
#include <stdio.h>

#define NUM 256
uint16_t adc_data[NUM];
//char adc_data_one_value[4096];
void startADC();
void stopADC();
void ADCGetValue();
#endif /* __ADC_SET_H */

