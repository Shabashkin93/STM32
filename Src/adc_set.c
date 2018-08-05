#include "adc_set.h"

extern ADC_HandleTypeDef hadc1;

void adc_start(){
    HAL_ADC_Start(&hadc1);
    HAL_ADC_Start_DMA (&hadc1, (uint32_t*)adc_data, NUM);
    HAL_TIM_Base_Start(&htim2);
    uart_send("adc is started\n\r",16);
}

void adc_stop(){
    HAL_ADC_Stop_DMA(&hadc1);
    HAL_ADC_Stop(&hadc1);
    uart_send("adc is stoped\n\r",15);
}

void adc_get_value(){
    for (int i =NUM-1; i>0; i--){
        printf(" %" PRIu32"" ,adc_data[i-1]);
        printf("\n");
    }
}
