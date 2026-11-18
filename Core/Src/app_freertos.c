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
#include "Formatter.h"

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
uint32_t MyBufferuserIntTask[ 256 ];
osStaticThreadDef_t MycontrolBlocuserIntTask;
const osThreadAttr_t userIntTask_attributes = {
  .name = "userIntTask",
  .stack_mem = &MyBufferuserIntTask[0],
  .stack_size = sizeof(MyBufferuserIntTask),
  .cb_mem = &MycontrolBlocuserIntTask,
  .cb_size = sizeof(MycontrolBlocuserIntTask),
  .priority = (osPriority_t) osPriorityNormal6,
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
  .priority = (osPriority_t) osPriorityNormal3,
};
/* Definitions for triggerHandling */
osThreadId_t triggerHandlingHandle;
uint32_t triggerHandlingbufferTask04[ 256 ];
osStaticThreadDef_t triggerHandlingblocTask04;
const osThreadAttr_t triggerHandling_attributes = {
  .name = "triggerHandling",
  .stack_mem = &triggerHandlingbufferTask04[0],
  .stack_size = sizeof(triggerHandlingbufferTask04),
  .cb_mem = &triggerHandlingblocTask04,
  .cb_size = sizeof(triggerHandlingblocTask04),
  .priority = (osPriority_t) osPriorityNormal2,
};
/* Definitions for screenPlotter */
osThreadId_t screenPlotterHandle;
uint32_t screenPlotterBuffer[ 512 ];
osStaticThreadDef_t screenPlotterBlocTask05;
const osThreadAttr_t screenPlotter_attributes = {
  .name = "screenPlotter",
  .stack_mem = &screenPlotterBuffer[0],
  .stack_size = sizeof(screenPlotterBuffer),
  .cb_mem = &screenPlotterBlocTask05,
  .cb_size = sizeof(screenPlotterBlocTask05),
  .priority = (osPriority_t) osPriorityNormal5,
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
uint8_t ADCreadingsBuffer01[ 100 * sizeof( uint16_t ) ];
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
/* Definitions for triggerLevel */
osMessageQueueId_t triggerLevelHandle;
uint8_t triggerLevelBuffer06[ 1 * sizeof( uint16_t ) ];
osStaticMessageQDef_t triggerLevelControlBlock06;
const osMessageQueueAttr_t triggerLevel_attributes = {
  .name = "triggerLevel",
  .cb_mem = &triggerLevelControlBlock06,
  .cb_size = sizeof(triggerLevelControlBlock06),
  .mq_mem = &triggerLevelBuffer06,
  .mq_size = sizeof(triggerLevelBuffer06)
};
/* Definitions for horizontalScale */
osMessageQueueId_t horizontalScaleHandle;
uint8_t horizontalScaleBuffer07[ 1 * sizeof( uint16_t ) ];
osStaticMessageQDef_t horizontalScaleControlBlock07;
const osMessageQueueAttr_t horizontalScale_attributes = {
  .name = "horizontalScale",
  .cb_mem = &horizontalScaleControlBlock07,
  .cb_size = sizeof(horizontalScaleControlBlock07),
  .mq_mem = &horizontalScaleBuffer07,
  .mq_size = sizeof(horizontalScaleBuffer07)
};
/* Definitions for verticalScale */
osMessageQueueId_t verticalScaleHandle;
uint8_t verticalScaleBuffer08[ 1 * sizeof( uint16_t ) ];
osStaticMessageQDef_t verticalScaleControlBlock08;
const osMessageQueueAttr_t verticalScale_attributes = {
  .name = "verticalScale",
  .cb_mem = &verticalScaleControlBlock08,
  .cb_size = sizeof(verticalScaleControlBlock08),
  .mq_mem = &verticalScaleBuffer08,
  .mq_size = sizeof(verticalScaleBuffer08)
};
/* Definitions for triggerEdge */
osMessageQueueId_t triggerEdgeHandle;
uint8_t triggerEdgeBuffer09[ 1 * sizeof( uint32_t ) ];
osStaticMessageQDef_t triggerEdgeControlBlock09;
const osMessageQueueAttr_t triggerEdge_attributes = {
  .name = "triggerEdge",
  .cb_mem = &triggerEdgeControlBlock09,
  .cb_size = sizeof(triggerEdgeControlBlock09),
  .mq_mem = &triggerEdgeBuffer09,
  .mq_size = sizeof(triggerEdgeBuffer09)
};
/* Definitions for adcBufferPass */
osMessageQueueId_t adcBufferPassHandle;
uint8_t adcBufferPassBuffer10[ 1 * sizeof( ADCFrame_t ) ];
osStaticMessageQDef_t adcBufferPassControlBlock10;
const osMessageQueueAttr_t adcBufferPass_attributes = {
  .name = "adcBufferPass",
  .cb_mem = &adcBufferPassControlBlock10,
  .cb_size = sizeof(adcBufferPassControlBlock10),
  .mq_mem = &adcBufferPassBuffer10,
  .mq_size = sizeof(adcBufferPassBuffer10)
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
  ADCreadingsHandle = osMessageQueueNew (100, sizeof(uint16_t), &ADCreadings_attributes);
  /* creation of time_voltagePairs */
  time_voltagePairsHandle = osMessageQueueNew (32, sizeof(uint16_t), &time_voltagePairs_attributes);
  /* creation of voltageValues */
  voltageValuesHandle = osMessageQueueNew (32, sizeof(uint16_t), &voltageValues_attributes);
  /* creation of triggerPosition */
  triggerPositionHandle = osMessageQueueNew (1, sizeof(uint8_t), &triggerPosition_attributes);
  /* creation of adcStarted */
  adcStartedHandle = osMessageQueueNew (1, sizeof(uint16_t), &adcStarted_attributes);
  /* creation of triggerLevel */
  triggerLevelHandle = osMessageQueueNew (1, sizeof(uint16_t), &triggerLevel_attributes);
  /* creation of horizontalScale */
  horizontalScaleHandle = osMessageQueueNew (1, sizeof(uint16_t), &horizontalScale_attributes);
  /* creation of verticalScale */
  verticalScaleHandle = osMessageQueueNew (1, sizeof(uint16_t), &verticalScale_attributes);
  /* creation of triggerEdge */
  triggerEdgeHandle = osMessageQueueNew (1, sizeof(uint32_t), &triggerEdge_attributes);
  /* creation of adcBufferPass */
  adcBufferPassHandle = osMessageQueueNew (1, sizeof(ADCFrame_t), &adcBufferPass_attributes);

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

  /* creation of screenPlotter */
  screenPlotterHandle = osThreadNew(screenPlotter, NULL, &screenPlotter_attributes);

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
	osDelay(100);
	initMetaInfo();
	osDelay(100);
	Spi_init();
	Spi_Format_Region(0, 7, 0, 131, 0xFF);
	LL_TIM_ClearFlag_UPDATE(TIM16);
	LL_TIM_EnableIT_UPDATE(TIM16);
	LL_TIM_EnableCounter(TIM16);

  /* Infinite loop */
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
	uint16_t trigger_val = 500, scale_x = 1000, scale_y = 1500, prev_x = 0, prev_y = 0, prev_t = 0;
	uint8_t charDispTop[16] = {"v max 0000mv 0.0"}, charDispBottom[16] = {"s max 000.0ms UP"}, changed = 1,dummyVar[2]={0};
	enum triggerEdge triggerState = FALLING, prev_trigger = RISING;
  	struct btn btnUp = {HIGH,8, GPIOC}, btnDown = {HIGH,9, GPIOC}, encoder_x_up = {HIGH, 9, GPIOA};
  	struct btn encoder_y_up = {HIGH, 11, GPIOA}, encoder_y_down = {HIGH, 12, GPIOA}, encoder_x_down = {HIGH, 10, GPIOA};
  /* Infinite loop */
  for(;;){
	  if(changed){
		  asciiConverter(scale_y, &charDispTop[9], &charDispTop[8], &charDispTop[7], &charDispTop[6]);
		  asciiConverter(scale_x, &charDispBottom[10], &charDispBottom[8], &charDispBottom[7], &charDispBottom[6]);
		  asciiConverter(trigger_val, &dummyVar[0],&dummyVar[1],&charDispTop[15],&charDispTop[13]);
		  if(triggerState == RISING){
			  charDispBottom[14] = 'U', charDispBottom[15] = 'P';
		  }else if(triggerState == FALLING){
			  charDispBottom[14] = 'D', charDispBottom[15] = 'N';
		  }
		  updateMetaDisplay(charDispTop, charDispBottom);
		  changed = 0;
	  }
	  btnHandler(&encoder_x_up);
	  btnHandler(&encoder_x_down);
	  if (encoder_x_up.btnState == FALL){
		  changed = 1;
	      if ((encoder_x_down.btnState == HIGH) || (encoder_x_down.btnState == RISE)){
	    	  scale_x = incx(scale_x);
	    	  changed = 1;
	      } else {
	    	  scale_x = decx(scale_x);
	    	  changed = 1;
	      }
	      changeTIM16Period(calcPeriod(scale_x));//use this new scale number to change the period for the adc
	  }
	  btnHandler(&encoder_y_up);
	  btnHandler(&encoder_y_down);
	  if (encoder_y_up.btnState == FALL){
		  if ((encoder_y_down.btnState == HIGH) || (encoder_y_down.btnState == RISE)){
			  if (scale_y < 3200){
				  scale_y = scale_y +100;
				  changed = 1;
			  }
		  } else if(scale_y -100 >= 100){
			  scale_y = scale_y -100;
			  changed = 1;
		  }
	  } prev_x = scale_xcheck(scale_x, prev_x); prev_y = scale_yCheck(scale_y, prev_y);
	  btnHandler(&btnUp);
	  btnHandler(&btnDown);                       // was trigger down
	  if((btnUp.btnState == FALL)){
		  trigger_val = triggerinc(trigger_val);
		  changed = 1;
	  }else if((btnDown.btnState == FALL)){
		  triggerState = triggerEdgeState(triggerState);
		  changed = 1;
	  } prev_trigger = triggerCheck(triggerState, prev_trigger); prev_t = Trigger_valCheck(trigger_val, prev_t);
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



	  for (uint32_t j = 0; j< 123456; j++ )
	  {
		if(LL_ADC_IsActiveFlag_EOC(ADC1)) {break;}
	  }
	  uint16_t adcResult = readADC();

	  uint16_t adcResultMV = convertADCtomv(adcResult);
	  osMessageQueuePut(ADCreadingsHandle, &adcResultMV, 0, osWaitForever);

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
	uint16_t adcMVArray[101] = {0};
	circ_bbuf_t adcBuffer = {adcMVArray,0,0,101,1,0};
	uint8_t samplesTaken = 0;
	uint16_t triggerLevel = 100;
	enum triggerEdge triggerEdge = RISING;

  /* Infinite loop */
  for(;;)
  {

	  osMessageQueueGet(triggerLevelHandle, &triggerLevel, 0, 0); //if there is something in this queue, the trigger level has changed
	  uint32_t edge;
	  if (osMessageQueueGet(triggerEdgeHandle, &edge, 0, 0) == osOK) triggerEdge = (enum triggerEdge)edge;
	  uint16_t adcMessage;
	  if (osMessageQueueGet(ADCreadingsHandle, &adcMessage, 0, osWaitForever) == osOK)
	  {
		  circ_bbuf_push(&adcBuffer, adcMessage);
		  samplesTaken++;

	  }

	  if (samplesTaken >= 100)
	  {
		  uint8_t trigger = triggerIndexParser(&adcBuffer, triggerEdge, triggerLevel);
		  samplesTaken = 0;
		  if(trigger)
		  {
			  osMessageQueuePut(triggerPositionHandle, &trigger, 0, osWaitForever);
			  osMessageQueuePut(adcBufferPassHandle, adcMVArray, 0, osWaitForever);
		  }

	  }



  }
  /* USER CODE END triggerHandling */
}

/* USER CODE BEGIN Header_screenPlotter */
/**
* @brief Function implementing the screenPlotter thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_screenPlotter */
void screenPlotter(void *argument)
{
  /* USER CODE BEGIN screenPlotter */
	uint8_t index = 0;
	static uint16_t adcResults[101] = {0};
	uint8_t shiftedIndex = 0;
	static uint16_t shiftedResults[100] = {0};
	uint8_t pixel = 0;

  /* Infinite loop */
  for(;;)
  {
		osMessageQueueGet(triggerPositionHandle, &index, 0, osWaitForever);
		osMessageQueueGet(adcBufferPassHandle, adcResults, 0, osWaitForever);
		if(index >= 50)
		{
			shiftedIndex = index - 50; //ex: index @ 75, start left at array 25
		}
		if (index < 50)
		{
			shiftedIndex = index+51; //ex: index @ 25, start at array 75
		}

		 for (uint8_t i = shiftedIndex; i < 100; i++)
		{
			shiftedResults[pixel] = adcResults[i];
			pixel++;
		}


		for (uint8_t i = 0; i < shiftedIndex; i++)
		{
			shiftedResults[pixel] = adcResults[i];
			pixel++;
		}
		pixel = 0;

		PlotDataPoints(shiftedResults);
  }
  /* USER CODE END screenPlotter */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

