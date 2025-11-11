/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    app_threadx.c
  * @author  MCD Application Team
  * @brief   ThreadX applicative file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "app_threadx.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "main.h"
#include <string.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define THREAD_STACK_SIZE 1024
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
uint8_t serial_thread_stack[THREAD_STACK_SIZE];
TX_THREAD serial_thread_ptr;

uint8_t led_thread_stack[THREAD_STACK_SIZE];
TX_THREAD led_thread_ptr;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */
void serial_thread_entry(ULONG inital_input);
void led_thread_entry(ULONG inital_input);
/* USER CODE END PFP */

/**
  * @brief  Application ThreadX Initialization.
  * @param memory_ptr: memory pointer
  * @retval int
  */
UINT App_ThreadX_Init(VOID *memory_ptr)
{
  UINT ret = TX_SUCCESS;
  TX_BYTE_POOL *byte_pool = (TX_BYTE_POOL*)memory_ptr;

  /* USER CODE BEGIN App_ThreadX_Init */
  (void)byte_pool;

  tx_thread_create(
  	  &serial_thread_ptr,
  	  "serial_thread",
	  serial_thread_entry,
  	  0x1234,
	  serial_thread_stack,
  	  THREAD_STACK_SIZE,
  	  15,
  	  15,
  	  TX_NO_TIME_SLICE,
  	  TX_AUTO_START
    );

  tx_thread_create(
	  &led_thread_ptr,
	  "led_thread",
	  led_thread_entry,
	  0x1234,
	  led_thread_stack,
	  THREAD_STACK_SIZE,
	  10,
	  15,
	  TX_NO_TIME_SLICE,
	  TX_AUTO_START
  );
  /* USER CODE END App_ThreadX_Init */

  return ret;
}

/**
  * @brief  MX_ThreadX_Init
  * @param  None
  * @retval None
  */
void MX_ThreadX_Init(void)
{
  /* USER CODE BEGIN  Before_Kernel_Start */

  /* USER CODE END  Before_Kernel_Start */

  tx_kernel_enter();

  /* USER CODE BEGIN  Kernel_Start_Error */

  /* USER CODE END  Kernel_Start_Error */
}

/* USER CODE BEGIN 1 */
void serial_thread_entry(ULONG inital_input)
{
	char msg[] = "UART Thread running! And now this has become a really reaaaally loooooong string!";

	while (1)
	{
		HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
		// .ioc file -> Middleware -> Azure RTOS -> ThreadX
		// --> TX_TIMER_TICKS_PER_SECOND = 100, which means 1 Tick is 10 ms
		// 400 / 10 = 40.
		tx_thread_sleep(40);
	}
}

void led_thread_entry(ULONG inital_input)
{
	while (1)
	{
		HAL_GPIO_TogglePin(LD4_GPIO_Port, LD4_Pin);
		tx_thread_sleep(4);
	}
}
/* USER CODE END 1 */
