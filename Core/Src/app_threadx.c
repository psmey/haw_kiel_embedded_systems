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
#include "stdio.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define TRACEX_BUFFER_SIZE 64000
#define THREAD_STACK_SIZE 1024
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
uint8_t tracex_buffer[TRACEX_BUFFER_SIZE];

uint8_t speedy_thread_stack[THREAD_STACK_SIZE];
TX_THREAD speedy_thread_ptr;

uint8_t slow_thread_stack[THREAD_STACK_SIZE];
TX_THREAD slow_thread_ptr;

TX_MUTEX mutex_ptr;
UINT status;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */
void speedy_thread_entry(ULONG initial_input);
void slow_thread_entry(ULONG initial_input);
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

  tx_trace_enable(&tracex_buffer, TRACEX_BUFFER_SIZE, 30);

  tx_thread_create(
	&speedy_thread_ptr,
	"speedy_thread",
	speedy_thread_entry,
	0x01234,
	speedy_thread_stack,
	THREAD_STACK_SIZE,
	5,
	5,
	TX_NO_TIME_SLICE,
	TX_AUTO_START
  );

  tx_thread_create(
	&slow_thread_ptr,
	"slow_thread",
	slow_thread_entry,
	0x01234,
	slow_thread_stack,
	THREAD_STACK_SIZE,
	15,
	15,
	TX_NO_TIME_SLICE,
	TX_AUTO_START
  );

  status = tx_mutex_create(&mutex_ptr, "mutex_ptr", TX_NO_INHERIT);
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
void speedy_thread_entry(ULONG initial_input)
{
	ULONG start_tick, end_tick, duration;

	while(1)
	{
		start_tick = tx_time_get();

		tx_thread_sleep(2);

		tx_mutex_get(&mutex_ptr, TX_WAIT_FOREVER);
		tx_thread_sleep(5);
		tx_mutex_put(&mutex_ptr);

		tx_thread_sleep(4);

		tx_mutex_get(&mutex_ptr, TX_WAIT_FOREVER);
		tx_thread_sleep(3);
		tx_mutex_put(&mutex_ptr);

		end_tick = tx_time_get();
		duration = end_tick - start_tick;

		char msg[64];
		sprintf(msg, "Speedy thread cycle: %lu ticks", duration);
		HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
	}
}

void slow_thread_entry(ULONG initial_input)
{
	ULONG start_tick, end_tick, duration;

	while(1)
	{
		start_tick = tx_time_get();

		tx_mutex_get(&mutex_ptr, TX_WAIT_FOREVER);
		tx_thread_sleep(12);
		tx_mutex_put(&mutex_ptr);

		tx_thread_sleep(8);

		tx_mutex_get(&mutex_ptr, TX_WAIT_FOREVER);
		tx_thread_sleep(11);
		tx_mutex_put(&mutex_ptr);

		tx_thread_sleep(9);

		end_tick = tx_time_get();
		duration = end_tick - start_tick;

		char msg[64];
		sprintf(msg, "Slow thread cycle: %lu ticks", duration);
		HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
	}
}
/* USER CODE END 1 */
