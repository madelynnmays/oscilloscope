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

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
typedef StaticTask_t osStaticThreadDef_t;
typedef StaticQueue_t osStaticMessageQDef_t;
typedef StaticSemaphore_t osStaticMutexDef_t;
typedef StaticSemaphore_t osStaticSemaphoreDef_t;
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
  .priority = (osPriority_t) osPriorityNormal1,
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
  .priority = (osPriority_t) osPriorityAboveNormal,
};
/* Definitions for triggerHandling */
osThreadId_t triggerHandlingHandle;
uint32_t triggerHandlingbufferTask04[ 128 ];
osStaticThreadDef_t triggerHandlingblocTask04;
const osThreadAttr_t triggerHandling_attributes = {
  .name = "triggerHandling",
  .stack_mem = &triggerHandlingbufferTask04[0],
  .stack_size = sizeof(triggerHandlingbufferTask04),
  .cb_mem = &triggerHandlingblocTask04,
  .cb_size = sizeof(triggerHandlingblocTask04),
  .priority = (osPriority_t) osPriorityNormal7,
};
/* Definitions for adcReadWrite */
osMutexId_t adcReadWriteHandle;
osStaticMutexDef_t adcReadWriteBlock01;
const osMutexAttr_t adcReadWrite_attributes = {
  .name = "adcReadWrite",
  .cb_mem = &adcReadWriteBlock01,
  .cb_size = sizeof(adcReadWriteBlock01),
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
/* Definitions for triggerPosition */
osMessageQueueId_t triggerPositionHandle;
uint8_t triggerPositionBuffer04[ 1 * sizeof( uint8_t ) ];
osStaticMessageQDef_t triggerPositionControlBlock04;
const osMessageQueueAttr_t triggerPosition_attributes = {
  .name = "triggerPosition",
  .cb_mem = &triggerPositionControlBlock04,
  .cb_size = sizeof(triggerPositionControlBlock04),
  .mq_mem = &triggerPositionBuffer04,
  .mq_size = sizeof(triggerPositionBuffer04)
};
/* Definitions for adcStarted */
osMessageQueueId_t adcStartedHandle;
uint8_t adcStartedBuffer05[ 1 * sizeof( uint16_t ) ];
osStaticMessageQDef_t adcStartedControlBlock05;
const osMessageQueueAttr_t adcStarted_attributes = {
  .name = "adcStarted",
  .cb_mem = &adcStartedControlBlock05,
  .cb_size = sizeof(adcStartedControlBlock05),
  .mq_mem = &adcStartedBuffer05,
  .mq_size = sizeof(adcStartedBuffer05)
};
/* Definitions for triggerHappened */
osSemaphoreId_t triggerHappenedHandle;
osStaticSemaphoreDef_t triggerHappenedControlBlock01;
const osSemaphoreAttr_t triggerHappened_attributes = {
  .name = "triggerHappened",
  .cb_mem = &triggerHappenedControlBlock01,
  .cb_size = sizeof(triggerHappenedControlBlock01),
};
/* Definitions for stopCheckingTrigger */
osSemaphoreId_t stopCheckingTriggerHandle;
osStaticSemaphoreDef_t stopCheckingTriggerControlBlock02;
const osSemaphoreAttr_t stopCheckingTrigger_attributes = {
  .name = "stopCheckingTrigger",
  .cb_mem = &stopCheckingTriggerControlBlock02,
  .cb_size = sizeof(stopCheckingTriggerControlBlock02),
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
  /* creation of adcReadWrite */
  adcReadWriteHandle = osMutexNew(&adcReadWrite_attributes);

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */
  /* creation of triggerHappened */
  triggerHappenedHandle = osSemaphoreNew(1, 1, &triggerHappened_attributes);

  /* creation of stopCheckingTrigger */
  stopCheckingTriggerHandle = osSemaphoreNew(1, 1, &stopCheckingTrigger_attributes);

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
  /* creation of triggerPosition */
  triggerPositionHandle = osMessageQueueNew (1, sizeof(uint8_t), &triggerPosition_attributes);
  /* creation of adcStarted */
  adcStartedHandle = osMessageQueueNew (1, sizeof(uint16_t), &adcStarted_attributes);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of userIntTask */
  userIntTaskHandle = osThreadNew(userIntTaskStart, NULL, &userIntTask_attributes);

  /* creation of voltReadingTask */
  voltReadingTaskHandle = osThreadNew(voltReadingTaskStart, NULL, &voltReadingTask_attributes);

  /* creation of triggerHandling */
  triggerHandlingHandle = osThreadNew(triggerHandling, NULL, &triggerHandling_attributes);

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
  /* Infinite loop */
	initMetaInfo();

for(;;)
  {

    osDelay(1);
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
  /* Infinite loop */
  for(;;)
  {
	uint8_t index;
	osMessageQueueGet(triggerPositionHandle, &index, 0, osWaitForever);
	sendMetaInfoWrite(index+48);
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

	  uint16_t message;
	  osMessageQueueGet(adcStartedHandle,&message,0,osWaitForever); //this tells us the ADC has been fired
	  osMutexAcquire(adcReadWriteHandle, osWaitForever);
	  for (uint16_t j = 0; j< 1234; j++ )
	  {
		if(LL_ADC_IsActiveFlag_EOC(ADC1)) {break;}
	  }
	  uint16_t adcResult = readADC();
	  osMutexRelease(adcReadWriteHandle);
	  uint16_t adcResultMV = convertADCtomv(adcResult);
	  osMessageQueuePut(ADCreadingsHandle, &adcResultMV, 0, osWaitForever);


	  osDelay(1);
  }
  /* USER CODE END voltReadingTask */
}

/* USER CODE BEGIN Header_triggerHandling */
/**
* @brief Function implementing the triggerHandling thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_triggerHandling */
void triggerHandling(void *argument)
{
  /* USER CODE BEGIN triggerHandling */
	uint16_t adcMVArray[120] = {0};
	circ_bbuf_t adcBuffer = {adcMVArray,0,0,121,1};
  /* Infinite loop */
  for(;;)
  {
	  //osMutexAcquire(adcReadWriteHandle, osWaitForever);
	  uint16_t adcMessage;
	  for (uint8_t j; j < 250; j++)
	  {
	  osMessageQueueGet(ADCreadingsHandle, &adcMessage, 0, osWaitForever);
	  circ_bbuf_push(&adcBuffer, adcMessage);
	  }
	  for (uint8_t i; i < 200; i++)
	  {
		  triggerIndexParser(&adcBuffer, RISING, 1000);
	  }

	  //osMutexRelease(adcReadWriteHandle);
    osDelay(1);
  }
  /* USER CODE END triggerHandling */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

