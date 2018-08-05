#include "console.h"

/*************************************************************************************************/

extern UART_HandleTypeDef huart3;
extern TIM_HandleTypeDef htim4;

/*************************************************************************************************/
uint8_t no_reset=1;             //флаг обновления счётчика watchdog таймера

const char *tick_value[10];
const char *start_msg="Nucleo launched\n\r";
const char *help_answer = 
    " Commands:\n"
    "reset -------reset controller\n"
    "ticks -------time in milliseconds\n"
    "led green ---toggle blue led\n"
    "pwm start ---start pwm blue led\n"
    "pwm stop ----stop pwm blue led\n"
    "flash write -write in 0x08100000\n"
    "flash read  -read on 0x08100000\n"
    "flash erase -erase sector\n\r";

void uart_send(char *str, size_t size) {
    HAL_UART_Transmit(&huart3, str, size, 100);
}

/*************************************************************************************************/


void help_answ(void (*transfer)(char *str, size_t size)){
    transfer(help_answer,strlen(help_answer));
}

/*************************************************************************************************/

void tick_answ(void (*transfer)(char *str, size_t size)){
    sprintf(tick_value, "%"PRIu32" ms \n\r", HAL_GetTick());
    transfer(tick_value,13);
}

/*************************************************************************************************/

void reset_answ(){
              no_reset=0;
}

/*************************************************************************************************/

void led_answ(void (*transfer)(char *str, size_t size)){
        HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_0);
        transfer("green led toggle\n\r",18);
}

/*************************************************************************************************/

void pwm_start(void (*transfer)(char *str, size_t size)){
        HAL_TIM_PWM_Start_IT (&htim4,TIM_CHANNEL_2);
        transfer("blue pwm start\n\r",16);
}

/*************************************************************************************************/

void pwm_stop(void (*transfer)(char *str, size_t size)){
        HAL_TIM_PWM_Stop_IT (&htim4,TIM_CHANNEL_2);
        transfer("blue pwm stop\n\r",15);
}

/*************************************************************************************************/

struct command {
    const char *name;
    void (*handle)();
};

/*************************************************************************************************/

struct command commands[]={
    {"help",      help_answ},
    {"tick",      tick_answ},
    {"reset",     reset_answ},
    {"led green",       led_answ},
    {"pwm start", pwm_start},
    {"pwm stop",  pwm_stop},
    {"flash write", flash_write_test},
    {"flash read", flash_read_test},
    {"flash erase", flash_erase_test},
    {"get adc", adc_get_value},
    {"adc stop", adc_stop},
    {"adc start", adc_start} 
};

/*************************************************************************************************/

/* monitor - получает данные и кладёт их в кольцевой буфер, сигнализируя если принят '\n'*/
void monitor(values_ring_buffer *options){
    options->rx_buf[options->idxIN++]=options->buf;
    options->word_lenght++;
    if (options->buf=='\n'){
        options->command_on=1;
    }
}

/*************************************************************************************************/

void command_handler(void (*transfer)(char *str, size_t size), uint8_t *buffer){
    for (int i=0;i<NUMBER_OF_TEAM;++i){
        if( !strncmp(commands[i].name, buffer, strlen(commands[i].name) )) {
            commands[i].handle(transfer);
        }
    }
}

/*************************************************************************************************/

void post_handler(values_ring_buffer *options){
    memset (options->buffer, '0', BUF_SIZE );
    HAL_UART_Receive_IT(&huart3, &options->buf, 1);
}

/*************************************************************************************************/

void console_uart_init(values_ring_buffer *options){
   options->idxIN=0;
   options->idxOUT=0;
   options->rx_buf[RX_BUF_SIZE];    //кольцевой буфер
   options->buffer[BUF_SIZE];       // буфер комманды
   options->word_lenght=0;          //длина принятого слова
   options->buf=0;                  //переменная хранящая принимаемый символ
   options->command_on=0;           //флаг что команда прочитана, те встречен "\n"
}

/*распознание команды и выполнение функции в случае успешного распознания*/

void console_uart(values_ring_buffer *options, void (*transfer)(char *str, size_t size)){
    if(options->command_on){
        for(int i=0; i < options->word_lenght; i++){
            options->buffer[i]=options->rx_buf[options->idxOUT++];
        }
        options->word_lenght=0;
        options->command_on=0;
        command_handler(transfer,options->buffer);
        post_handler(options);
    }
}
