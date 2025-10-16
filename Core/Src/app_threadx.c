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
uint8_t LED_thread_stack[THREAD_STACK_SIZE];
uint8_t BTN_thread_stack[THREAD_STACK_SIZE];

TX_THREAD LED_thread_ptr;
TX_THREAD BTN_thread_ptr;

TX_SEMAPHORE LED_semaphore;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */
void LED_thread_entry(ULONG inital_input);
void BTN_thread_entry(ULONG inital_input);
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

  tx_semaphore_create(&LED_semaphore, "LED_Toggle_Semaphoe", 1);

  tx_thread_create(
	  &LED_thread_ptr,
	  "LED_thread",
	  LED_thread_entry,
	  0x1234,
	  LED_thread_stack,
	  THREAD_STACK_SIZE,
	  15,
	  15,
	  TX_NO_TIME_SLICE,
	  TX_AUTO_START
  );

  tx_thread_create(
	  &BTN_thread_ptr,
	  "BTN_thread",
	  BTN_thread_entry,
	  0x1234,
	  BTN_thread_stack,
	  THREAD_STACK_SIZE,
	  15,
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
void LED_thread_entry(ULONG inital_input)
{
	UINT status = 0;

	while(1)
	{
		status = tx_semaphore_get(&LED_semaphore, TX_WAIT_FOREVER);

		if(!status)
		{
			HAL_GPIO_TogglePin(LD4_GPIO_Port, LD4_Pin);
		}
	}
}

void BTN_thread_entry(ULONG initial_input)
{
	while(1)
	{
		UINT button_pressed = HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin);

		if(button_pressed)
		{
			tx_semaphore_put(&LED_semaphore);
		}
		else
		{
			tx_thread_sleep(10);
		}
	}
}
/* USER CODE END 1 */
