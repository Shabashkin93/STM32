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
#include "hts221.h"

#define RECEIVE_BUFFER_SIZE 256
#define NUMBER_OF_COMMANDS 13
#define BUFFER_SIZE 64

extern UART_HandleTypeDef huart3;                                                                             
extern TIM_HandleTypeDef htim4;
extern uint8_t noWWDGReset;
extern const char *startMessage;
extern const char *helpAnswer;

typedef struct {
    uint8_t idxIN;
    uint8_t idxOUT;
    uint8_t circularReceiveBuffer[RECEIVE_BUFFER_SIZE];
    uint8_t commandBuffer[BUFFER_SIZE];
    uint8_t lengthReceivedMessage;
    uint8_t receivedSymbol;
    uint8_t commandWasRead;
} RingBuffer;

void initCLIUART(RingBuffer *options);
void sendingHelpMessage(void (*transfer)(uint8_t *str, size_t size));
void sendingTickValue(void (*transfer)(uint8_t *str, size_t size));
void rebootThisDevice();
void toggleGreenLed(void (*transfer)(uint8_t *str, size_t size));
void startPWM(void (*transfer)(uint8_t *str, size_t size));
void stopPWM(void (*transfer)(uint8_t *str, size_t size));
void monitor(RingBuffer *options);
void handlerCLIUART(RingBuffer *options,void (*transfer)(uint8_t *str, size_t size));
void sendingToUART(uint8_t *str, size_t size);
void commandHandler(void (*transfer)(uint8_t *str, size_t size), uint8_t *str);
void postHandler(RingBuffer *options);
#endif /* __CONSOLE_H */
