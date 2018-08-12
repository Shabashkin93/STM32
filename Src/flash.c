#include "flash.h"

HAL_StatusTypeDef	flash_ok = HAL_ERROR;

/* for write use sector 8 with range of addresses 0x0810 0000 - 0x0813 FFFF*/

void flashWriteTest(){
		HAL_FLASH_Unlock();
        HAL_FLASH_OB_Unlock();
        HAL_UART_Transmit(&huart3, "unlock flash\n\r",14,100);
	flash_ok = HAL_ERROR;
	while(flash_ok != HAL_OK){
		flash_ok = HAL_FLASH_Program_IT(TYPEPROGRAM_WORD, ADDRESS_START, "STMP");
        HAL_UART_Transmit(&huart3, "write flash\n\r",13,100);
	}
    HAL_FLASH_OB_Lock();
	HAL_FLASH_Lock();
    HAL_UART_Transmit(&huart3, "lock flash\n\r",12,100);
}

/******************************************************************************/

void flashReadTest(void (*transfer)(char *str, size_t size)){
    char *buf[32];
/*    sprintf(buf, "%d", value);*/
    sprintf(buf, "%"PRIu32, (*(__IO uint32_t*)(ADDRESS_START)));
    transfer(buf,32);
}

void flashEraseTest(){
	HAL_FLASH_Unlock();
    HAL_FLASH_OB_Unlock();
	FLASH_Erase_Sector(FLASH_SECTOR_17, VOLTAGE_RANGE_3);
    HAL_FLASH_OB_Lock();
	HAL_FLASH_Lock();
    HAL_UART_Transmit(&huart3, "erase ok\n\r",10,100);
}

