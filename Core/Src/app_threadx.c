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

uint8_t thread_d_producer_stack[THREAD_STACK_SIZE];
TX_THREAD thread_d_producer;

uint8_t thread_a_stack[THREAD_STACK_SIZE];
TX_THREAD thread_a;

uint8_t thread_b_stack[THREAD_STACK_SIZE];
TX_THREAD thread_b;

uint8_t thread_c_stack[THREAD_STACK_SIZE];
TX_THREAD thread_c;

TX_QUEUE queue_a;
static CHAR queue_a_memory[24];

TX_QUEUE queue_b;
static CHAR queue_b_memory[24];

TX_QUEUE queue_c;
static CHAR queue_c_memory[24];

uint32_t count_a;
uint32_t count_b;
uint32_t count_c;
uint32_t count_d;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */
void thread_d_producer_entry(ULONG initial_input);
void thread_a_entry(ULONG initial_input);
void thread_b_entry(ULONG initial_input);
void thread_c_entry(ULONG initial_input);
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
	&thread_d_producer,
	"thread_d_producer",
	thread_d_producer_entry,
	0x01234,
	thread_d_producer_stack,
	THREAD_STACK_SIZE,
	1,
	1,
	TX_NO_TIME_SLICE,
	TX_AUTO_START
  );

  tx_thread_create(
  	&thread_a,
  	"thread_a",
	thread_a_entry,
  	0x01234,
	thread_a_stack,
  	THREAD_STACK_SIZE,
  	1,
  	1,
  	TX_NO_TIME_SLICE,
  	TX_AUTO_START
  );

  tx_thread_create(
  	&thread_b,
  	"thread_b",
	thread_b_entry,
  	0x01234,
	thread_b_stack,
  	THREAD_STACK_SIZE,
  	1,
  	1,
  	TX_NO_TIME_SLICE,
  	TX_AUTO_START
  );

  tx_thread_create(
  	&thread_c,
  	"thread_c",
	thread_c_entry,
  	0x01234,
	thread_c_stack,
  	THREAD_STACK_SIZE,
  	1,
  	1,
  	TX_NO_TIME_SLICE,
  	TX_AUTO_START
  );

  tx_queue_create(&queue_a, "queue", 3, &queue_a_memory, sizeof(queue_a_memory));
  tx_queue_create(&queue_b, "queue", 3, &queue_b_memory, sizeof(queue_b_memory));
  tx_queue_create(&queue_c, "queue", 3, &queue_c_memory, sizeof(queue_c_memory));
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
void thread_d_producer_entry(ULONG initial_input) {
	char msg[24];

	while(1)
	{
		for (int i = 0; i < 3; i++)
		{
			tx_queue_send(&queue_a, msg, TX_NO_WAIT);
			tx_queue_send(&queue_b, msg, TX_NO_WAIT);
			tx_queue_send(&queue_c, msg, TX_NO_WAIT);
		}

		count_d++;
		tx_thread_relinquish();
	}
}

void thread_a_entry(ULONG initial_input) {
	char msg[24];

	while(1)
	{
		for (int i = 0; i < 3; i++)
		{
			tx_queue_receive(&queue_a, msg, TX_WAIT_FOREVER);
		}

		count_a++;
		tx_thread_relinquish();
	}

}

void thread_b_entry(ULONG initial_input) {
	char msg[24];

	while(1)
	{
		for (int i = 0; i < 3; i++)
		{
			tx_queue_receive(&queue_b, msg, TX_WAIT_FOREVER);
		}

		count_b++;
		tx_thread_relinquish();
	}
}

void thread_c_entry(ULONG initial_input) {
	char msg[24];

	while(1)
	{
		for (int i = 0; i < 3; i++) {
			tx_queue_receive(&queue_c, msg, TX_WAIT_FOREVER);
		}

		count_c++;
		tx_thread_relinquish();
	}
}
/* USER CODE END 1 */
