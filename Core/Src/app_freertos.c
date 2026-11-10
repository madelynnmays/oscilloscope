/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : app_freertos.c
  * Description        : FreeRTOS applicative file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
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
#include "app_freertos.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "Screen.h"
#include "Userint.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
typedef StaticTask_t osStaticThreadDef_t;
typedef StaticQueue_t osStaticMessageQDef_t;
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 128 * 4
};
/* Definitions for userIntTask */
osThreadId_t userIntTaskHandle;
uint32_t MyBufferuserIntTask[ 128 ];
osStaticThreadDef_t MycontrolBlocuserIntTask;
const osThreadAttr_t userIntTask_attributes = {
  .name = "userIntTask",
  .stack_mem = &MyBufferuserIntTask[0],
  .stack_size = sizeof(MyBufferuserIntTask),
  .cb_mem = &MycontrolBlocuserIntTask,
  .cb_size = sizeof(MycontrolBlocuserIntTask),
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for voltReadingTask */
osThreadId_t voltReadingTaskHandle;
uint32_t MyBuffervoltReadingTask[ 128 ];
osStaticThreadDef_t MycontrolBlocvoltReadingTask;
const osThreadAttr_t voltReadingTask_attributes = {
  .name = "voltReadingTask",
  .stack_mem = &MyBuffervoltReadingTask[0],
  .stack_size = sizeof(MyBuffervoltReadingTask),
  .cb_mem = &MycontrolBlocvoltReadingTask,
  .cb_size = sizeof(MycontrolBlocvoltReadingTask),
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for ADCreadings */
osMessageQueueId_t ADCreadingsHandle;
uint8_t ADCreadingsBuffer01[ 32 * sizeof( uint16_t ) ];
osStaticMessageQDef_t ADCreadingsControlBlock01;
const osMessageQueueAttr_t ADCreadings_attributes = {
  .name = "ADCreadings",
  .cb_mem = &ADCreadingsControlBlock01,
  .cb_size = sizeof(ADCreadingsControlBlock01),
  .mq_mem = &ADCreadingsBuffer01,
  .mq_size = sizeof(ADCreadingsBuffer01)
};
/* Definitions for time_voltagePairs */
osMessageQueueId_t time_voltagePairsHandle;
uint8_t time_voltagePairsBuffer02[ 32 * sizeof( uint16_t ) ];
osStaticMessageQDef_t time_voltagePairsControlBlock02;
const osMessageQueueAttr_t time_voltagePairs_attributes = {
  .name = "time_voltagePairs",
  .cb_mem = &time_voltagePairsControlBlock02,
  .cb_size = sizeof(time_voltagePairsControlBlock02),
  .mq_mem = &time_voltagePairsBuffer02,
  .mq_size = sizeof(time_voltagePairsBuffer02)
};
/* Definitions for voltageValues */
osMessageQueueId_t voltageValuesHandle;
uint8_t voltageValuesBuffer03[ 32 * sizeof( uint16_t ) ];
osStaticMessageQDef_t voltageValuesControlBlock03;
const osMessageQueueAttr_t voltageValues_attributes = {
  .name = "voltageValues",
  .cb_mem = &voltageValuesControlBlock03,
  .cb_size = sizeof(voltageValuesControlBlock03),
  .mq_mem = &voltageValuesBuffer03,
  .mq_size = sizeof(voltageValuesBuffer03)
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
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
  /* creation of ADCreadings */
  ADCreadingsHandle = osMessageQueueNew (32, sizeof(uint16_t), &ADCreadings_attributes);
  /* creation of time_voltagePairs */
  time_voltagePairsHandle = osMessageQueueNew (32, sizeof(uint16_t), &time_voltagePairs_attributes);
  /* creation of voltageValues */
  voltageValuesHandle = osMessageQueueNew (32, sizeof(uint16_t), &voltageValues_attributes);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of userIntTask */
  userIntTaskHandle = osThreadNew(userIntTaskStart, NULL, &userIntTask_attributes);

  /* creation of voltReadingTask */
  voltReadingTaskHandle = osThreadNew(voltReadingTaskStart, NULL, &voltReadingTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}
/* USER CODE BEGIN Header_StartDefaultTask */
/**
* @brief Function implementing the defaultTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN defaultTask */
	Spi_init();
  /* Infinite loop */
  for(;;)
  {
	    osDelay(5);
  }
  /* USER CODE END defaultTask */
}

/* USER CODE BEGIN Header_userIntTaskStart */
/**
* @brief Function implementing the userIntTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_userIntTaskStart */
void userIntTaskStart(void *argument)
{
  /* USER CODE BEGIN userIntTask */
	uint16_t scale = 0;
  	//struct btn btnUp = {HIGH,11, GPIOA};
  	//struct btn btnDown = {HIGH,12, GPIOA};

  	struct btn encoderA = {HIGH, 9, GPIOA};
  	struct btn encoderB = {HIGH, 10, GPIOA};
  /* Infinite loop */
  for(;;)
  {
	  btnHandler(&encoderA);
	  btnHandler(&encoderB);
	  if (encoderA.btnState == FALL){
	      if ((encoderB.btnState == HIGH) || (encoderB.btnState == RISE)){
	          if (scale < 50) scale++;
	      } else {
	          if (scale > 0) scale--;
	      }
	  }

	  /*
	  	btnHandler(&btnUp);
	  	btnHandler(&btnDown);                       // was btnUp twice
	  	if((btnUp.btnState == HIGH) & (btnDown.btnState == RISE))
	  	{

	  	}
	  	else if ((btnUp.btnState == LOW) & (btnDown.btnState == RISE))
	  	{

	  	}
	  	*/
    osDelay(1);
  }
  /* USER CODE END userIntTask */
}

/* USER CODE BEGIN Header_voltReadingTaskStart */
/**
* @brief Function implementing the voltReadingTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_voltReadingTaskStart */
void voltReadingTaskStart(void *argument)
{
  /* USER CODE BEGIN voltReadingTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END voltReadingTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

