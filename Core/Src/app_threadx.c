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
#define MESSAGE_LENGTH 64

// a char is 8 bits
#define CHAR_IN_ONE_BYTE 4
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
uint8_t tracex_buffer[TRACEX_BUFFER_SIZE];

uint8_t thread_gatekeeper_stack[THREAD_STACK_SIZE];
TX_THREAD thread_gatekeeper;

uint8_t thread_1_stack[THREAD_STACK_SIZE];
TX_THREAD thread_1;

uint8_t thread_2_stack[THREAD_STACK_SIZE];
TX_THREAD thread_2;

TX_QUEUE queue;
static CHAR queue_memory[CHAR_IN_ONE_BYTE * MESSAGE_LENGTH * 64];
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */
void thread_gatekeeper_entry(ULONG initial_input);
void thread_1_entry(ULONG initial_input);
void thread_2_entry(ULONG initial_input);
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

  tx_queue_create(&queue, "queue", 16, &queue_memory, sizeof(queue_memory));

  tx_thread_create(
	&thread_gatekeeper,
	"thread_gatekeeper",
	thread_gatekeeper_entry,
	0x01234,
	thread_gatekeeper_stack,
	THREAD_STACK_SIZE,
	1,
	1,
	TX_NO_TIME_SLICE,
	TX_AUTO_START
  );

  tx_thread_create(
  	&thread_1,
  	"thread_1",
	thread_1_entry,
  	0x01234,
	thread_1_stack,
  	THREAD_STACK_SIZE,
  	1,
  	1,
  	TX_NO_TIME_SLICE,
  	TX_AUTO_START
  );

  tx_thread_create(
  	&thread_2,
  	"thread_2",
	thread_2_entry,
  	0x01234,
	thread_2_stack,
  	THREAD_STACK_SIZE,
  	1,
  	1,
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
void thread_1_entry(ULONG initial_input) {
	char msg[MESSAGE_LENGTH];
	ULONG count, time;

	while(1)
	{
		count++;
		time = tx_time_get();

		sprintf(msg, "Thread 1: executed %lu times, current system time: %lu.", count, time);

		tx_queue_send(&queue, msg, TX_NO_WAIT);

		tx_thread_sleep(8);
	}
}

void thread_2_entry(ULONG initial_input) {
	char msg[MESSAGE_LENGTH];
	ULONG count, time;

	while(1)
	{
		count++;
		time = tx_time_get();

		sprintf(msg, "Thread 2: executed %lu times, current system time: %lu.", count, time);

		tx_queue_send(&queue, msg, TX_NO_WAIT);

		tx_thread_sleep(12);
	}
}

void thread_gatekeeper_entry(ULONG initial_input) {
	char msg[MESSAGE_LENGTH];

	while(1)
	{
		tx_queue_receive(&queue, msg, TX_WAIT_FOREVER);

		HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);

		tx_thread_sleep(30);
	}

}

/* USER CODE END 1 */
