#ifndef __FLASH_H

#define __FLASH_H
#define ADDRESS_START 0x08100000

#include "stm32f7xx_hal.h"
#include <string.h> 
#include <stdio.h>
#include <inttypes.h>
#include "usart.h"
#include <inttypes.h>
#include <stdint.h>
#include <stddef.h> 
#include "stm32f7xx_hal_flash.h"
#include "lwip/opt.h"
#include "lwip/arch.h"
#include "lwip/api.h"

void eth_send(char *str, size_t size);
void tcpecho(void);
void tcpcounter(void);
struct netconn *conn, *newconn;

#endif
