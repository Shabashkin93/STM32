/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * Copyright (c) 2018 STMicroelectronics International N.V. 
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"

/* USER CODE BEGIN Includes */     
#include "flash.h"
#include "console.h"
#include "lcd2004a.h"
/* USER CODE END Includes */

/* Variables -----------------------------------------------------------------*/
osThreadId defaultTaskHandle;
osThreadId myTask02Handle;

/* USER CODE BEGIN Variables */
extern RingBuffer uartc_3;
extern I2C_HandleTypeDef hi2c2;
char str[40];
struct communicationParameters LCD_1 = {&hi2c2, 0x27};
/* USER CODE END Variables */

/* Function prototypes -------------------------------------------------------*/
void StartDefaultTask(void const * argument);
void StartTask02(void const * argument);

extern void MX_LWIP_Init(void);
void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* USER CODE BEGIN FunctionPrototypes */
extern void tcpEcho(void);
/* USER CODE END FunctionPrototypes */

/* Hook prototypes */

/* Init FreeRTOS */

void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
       
  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of myTask02 */
  osThreadDef(myTask02, StartTask02, osPriorityIdle, 0, 128);
  myTask02Handle = osThreadCreate(osThread(myTask02), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */
}

/* StartDefaultTask function */
void StartDefaultTask(void const * argument)
{
  /* init code for LWIP */
  MX_LWIP_Init();

  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  tcpEcho();
  
/*  char str[100];
  LCD_ini(LCD_1);
  sprintf(str,"STM32F767ZI");
      LCD_String(LCD_1, str);
      LCD_SetCursor(LCD_1, 3, 0);
      sprintf(str,"Nucleo");
      LCD_String(LCD_1, str);
      HAL_Delay(2000);
      LCD_Clear(LCD_1);
      LCD_SetCursor(LCD_1, 0, 4);
      LCD_SendChar(LCD_1, 's');
      LCD_SetCursor(LCD_1, 1, 8);
      LCD_SendChar(LCD_1, 't');
      LCD_SetCursor(LCD_1, 2, 12);
      LCD_SendChar(LCD_1, 'm');
      LCD_SetCursor(LCD_1, 3, 16);
      LCD_SendChar(LCD_1, '3');
      LCD_SendChar(LCD_1, '2');*/
  /* USER CODE END StartDefaultTask */
}

/* StartTask02 function */
void StartTask02(void const * argument)
{
  /* USER CODE BEGIN StartTask02 */
    for(;;){
        handlerCLIUART(&uartc_3, sendingToUART);
        for(int i =65535; i>0; i--){
            TIM4->CCR2=i;/* для PWM , изменяется скважность*/
        }
        osDelay(1);
    }
  /* USER CODE END StartTask02 */
}

/* USER CODE BEGIN Application */
     
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
