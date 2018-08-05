#ifndef __FLASH_H

#define __FLASH_H
#define ADDRESS_START 0x08120000

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
#include "console.h"

void flash_write_test();
void flash_read_test(void (*transfer)(char *str, size_t size));
void flash_erase_test();

#endif
