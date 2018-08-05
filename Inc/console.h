#ifndef __CONSOLE_H
	
#define __CONSOLE_H
	
#include "stm32f7xx_hal.h"
#include <string.h>
#include <stdio.h>
#include <inttypes.h>	
#include "usart.h"
#include <stdint.h>
#include "gpio.h"
#include "tim.h"
#include <stddef.h>
#include "flash.h"
#include <stdlib.h>
#include "adc_set.h"

#define RX_BUF_SIZE 256
#define NUMBER_OF_TEAM 12
#define BUF_SIZE 64   


extern UART_HandleTypeDef huart3;                                                                             
extern TIM_HandleTypeDef htim4;
extern uint8_t no_reset;               //флаг указывающий обновлять или нет счётчик watchdog таймера

extern const char *start_msg;          //сообщение отправляемое при старте контроллера
extern const char *help_answer;        //сообщение с описанием возможных команд

typedef struct {
    uint8_t idxIN;
    uint8_t idxOUT;
    uint8_t rx_buf[RX_BUF_SIZE];    //кольцевой буфер
    uint8_t buffer[BUF_SIZE];       // буфер комманды
    uint8_t word_lenght;          //длина принятого слова
    uint8_t buf;                  //переменная хранящая принимаемый символ
    uint8_t command_on;           //флаг что команда прочитана, те встречен "\n"
} values_ring_buffer;

void console_uart_init(values_ring_buffer *options);
void help_answ(void (*transfer)(char *str, size_t size));
void tick_answ(void (*transfer)(char *str, size_t size));
void reset_answ();
void led_answ(void (*transfer)(char *str, size_t size));
void pwm_start(void (*transfer)(char *str, size_t size));
void pwm_stop(void (*transfer)(char *str, size_t size));
void monitor(values_ring_buffer *options);
void console_uart(values_ring_buffer *options,void (*transfer)(char *str, size_t size));
void uart_send(char *str, size_t size);
void command_handler(void (*transfer)(char *str, size_t size), uint8_t *str);
void post_handler(values_ring_buffer *options);
#endif /* __CONSOLE_H */
