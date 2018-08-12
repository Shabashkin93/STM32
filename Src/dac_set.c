#include "dac_set.h"

extern TIM_HandleTypeDef htim7;
extern DAC_HandleTypeDef hdac;
static uint16_t sine[AMOUNT_OF_POINTS * 4];

void DACSet(){
    const float A = 2047;
    const float PI = 3.1415927;
    for(int i = 0; i < AMOUNT_OF_POINTS * 4; i++) {
      /* 2048 It is necessary to deduce the sine above the axis. */
        sine[i] = 2048 + (int16_t)(round(A * sin((i * PI) / (AMOUNT_OF_POINTS * 2.0))));
    }
}

void DACStart(){
    HAL_TIM_Base_Start(&htim7);
    HAL_DAC_Start(&hdac,DAC_CHANNEL_1);
    HAL_DAC_Start_DMA(&hdac, DAC_CHANNEL_1, (uint32_t*)sine, AMOUNT_OF_POINTS * 4, DAC_ALIGN_12B_R);
}

void DACStop(){
    HAL_DAC_Stop_DMA (&hdac, DAC_CHANNEL_1);
    HAL_DAC_Stop (&hdac, DAC_CHANNEL_1);
    HAL_TIM_Base_Stop(&htim7);
}
