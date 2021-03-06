#include "console.h"

/* Variables ---------------------------------------------------------*/
extern UART_HandleTypeDef huart3;
extern TIM_HandleTypeDef htim4;
uint8_t noWWDGReset=1;
const char *startMessage ="Nucleo launched\n\r";
const char *helpAnswer =
    " Commands:\n"
    "reset -------reset controller\n"
    "ticks -------time in milliseconds\n"
    "led green ---toggle blue led\n"
    "pwm start ---start pwm blue led\n"
    "pwm stop ----stop pwm blue led\n"
    "flash write -write in 0x08100000\n"
    "flash read  -read on 0x08100000\n"
    "flash erase -erase sector\n\r";

void sendingToUART(uint8_t *str, size_t size) {
    char tempStr[size];
    sprintf(tempStr, "%s", str);
    HAL_UART_Transmit(&huart3, (uint8_t*)&tempStr, size, 100);
}

/*************************************************************************************************/


void sendingHelpMessage(void (*transfer)(uint8_t *str, size_t size)){
    char tempStr[strlen(helpAnswer)];
    sprintf(tempStr, "%s", helpAnswer);
    transfer((uint8_t*)&tempStr,strlen(helpAnswer));
}

/*************************************************************************************************/

void sendingTickValue(void (*transfer)(uint8_t *str, size_t size)){
    char tickValue[16];
    sprintf(tickValue, "%" PRIu32 "ms" "\n\n", HAL_GetTick());
    transfer((uint8_t*)&tickValue,16);
}

/*************************************************************************************************/

void rebootThisDevice(){
  noWWDGReset=0;
}

/*************************************************************************************************/

void toggleGreenLed(void (*transfer)(uint8_t *str, size_t size)){
        HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_0);
        char tempStr[18]={0};
        sprintf(tempStr, "green led toggle\n\r");
        transfer((uint8_t*)&tempStr,18);
}

/*************************************************************************************************/

void startPWM(void (*transfer)(uint8_t *str, size_t size)){
        HAL_TIM_PWM_Start_IT (&htim4,TIM_CHANNEL_2);
        char tempStr[16]={0};
        sprintf(tempStr, "blue pwm start\n\r");
        transfer((uint8_t*)&tempStr,16);
}

/*************************************************************************************************/

void stopPWM(void (*transfer)(uint8_t *str, size_t size)){
        HAL_TIM_PWM_Stop_IT (&htim4,TIM_CHANNEL_2);
        char tempStr[15]={0};
        sprintf(tempStr, "blue pwm stop\n\r");
        transfer((uint8_t*)&tempStr,15);
}

/*************************************************************************************************/

struct command {
    const char *nameCommand;
    void (*command)();
};

/*************************************************************************************************/

struct command commands[]={
    {"help",      sendingHelpMessage},
    {"tick",      sendingTickValue},
    {"reset",     rebootThisDevice},
    {"led green",       toggleGreenLed},
    {"pwm start", startPWM},
    {"pwm stop",  stopPWM},
    {"flash write", flashWriteTest},
    {"flash read", flashReadTest},
    {"flash erase", flashEraseTest},
    {"get adc", ADCGetValue},
    {"adc stop", stopADC},
    {"adc start", startADC},
    {"hts", initHTS221}
};

/*************************************************************************************************/

/* monitor - receives the data and puts them in the ring buffer, signaling if accepted. '\n'*/
void monitor(RingBuffer *options){
    options->circularReceiveBuffer[options->idxIN++]=options->receivedSymbol;
    options->lengthReceivedMessage++;
    if (options->receivedSymbol=='\n'){
        options->commandWasRead=1;
    }
}

/**
 * @brief commandHandler processes received commands.
 * @param transfer data transmitter: str - data, size - size data
 * @param buffer - ring buffer receive data
 * @return None
 */
void commandHandler(void (*transfer)(uint8_t *str, size_t size), uint8_t *buffer){
    for (int i=0;i<NUMBER_OF_COMMANDS;++i){
        if( !strncmp(commands[i].nameCommand, buffer, strlen(commands[i].nameCommand) )) {
            commands[i].command(transfer);
        }
    }
}

/*************************************************************************************************/

void postHandler(RingBuffer *options){
    memset (options->commandBuffer, '0', BUFFER_SIZE );
    HAL_UART_Receive_IT(&huart3, &options->receivedSymbol, 1);
}

/*************************************************************************************************/

void initCLIUART(RingBuffer *options){
   options->idxIN=0;
   options->idxOUT=0;
   options->circularReceiveBuffer[RECEIVE_BUFFER_SIZE];
   options->commandBuffer[BUFFER_SIZE];
   options->lengthReceivedMessage=0;
   options->receivedSymbol=0;
   options->commandWasRead=0;
}

/*распознание команды и выполнение функции в случае успешного распознания*/

void handlerCLIUART(RingBuffer *options, void (*transfer)(uint8_t *str, size_t size)){
    if(options->commandWasRead){
        for(int i=0; i < options->lengthReceivedMessage; i++){
            options->commandBuffer[i]=options->circularReceiveBuffer[options->idxOUT++];
        }
        options->lengthReceivedMessage=0;
        options->commandWasRead=0;
        commandHandler(transfer,options->commandBuffer);
        postHandler(options);
    }
}
