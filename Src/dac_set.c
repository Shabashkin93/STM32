#include "dac_set.h"

extern TIM_HandleTypeDef htim7;
extern DAC_HandleTypeDef hdac;

void dac_set(){
    const float A = 2047;
    const float PI = 3.1415927;
    for(int i = 0; i < AMOUNT_OF_POINTS * 4; i++) {
        sine[i] = 2048 + (int16_t)(round(A * sin((i * PI) / (AMOUNT_OF_POINTS * 2.0))));// 2048 нужно для выведения синуса выше оси
    }
}

void dac_start(){
    HAL_TIM_Base_Start(&htim7);
    HAL_DAC_Start(&hdac,DAC_CHANNEL_1);
    HAL_DAC_Start_DMA(&hdac, DAC_CHANNEL_1, (uint32_t*)sine, AMOUNT_OF_POINTS * 4, DAC_ALIGN_12B_R);
}

void dac_stop(){
    HAL_DAC_Stop_DMA (&hdac, DAC_CHANNEL_1);
    HAL_DAC_Stop (&hdac, DAC_CHANNEL_1);
    HAL_TIM_Base_Stop(&htim7);
}
