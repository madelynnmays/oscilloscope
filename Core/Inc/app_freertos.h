/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : app_freertos.h
  * Description        : FreeRTOS applicative header file
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __APP_FREERTOS_H
#define __APP_FREERTOS_H

#ifdef __cplusplus
extern "C" {
#endif
/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os2.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "VoltMeasure.h"
#include "Trigger.h"
#include "MetaInfoDisplay.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
typedef struct {
    uint16_t values[101];
} ADCFrame_t; // to make cubemx happy so i can allocated enough size for the adc array passing queue
/* USER CODE END PD */

/* Exported macro -------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */
extern osThreadId_t defaultTaskHandle;
extern osThreadId_t userIntTaskHandle;
extern osThreadId_t voltReadingTaskHandle;
extern osThreadId_t triggerHandlingHandle;
extern osThreadId_t screenPlotterHandle;
extern osMutexId_t adcReadWriteHandle;
extern osMessageQueueId_t ADCreadingsHandle;
extern osMessageQueueId_t time_voltagePairsHandle;
extern osMessageQueueId_t voltageValuesHandle;
extern osMessageQueueId_t triggerPositionHandle;
extern osMessageQueueId_t adcStartedHandle;
extern osMessageQueueId_t triggerLevelHandle;
extern osMessageQueueId_t horizontalScaleHandle;
extern osMessageQueueId_t verticalScaleHandle;
extern osMessageQueueId_t triggerEdgeHandle;
extern osMessageQueueId_t adcBufferPassHandle;
extern osSemaphoreId_t triggerHappenedHandle;
extern osSemaphoreId_t stopCheckingTriggerHandle;

/* Exported function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void userIntTaskStart(void *argument);
void voltReadingTaskStart(void *argument);
void triggerHandling(void *argument);
void screenPlotter(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

#ifdef __cplusplus
}
#endif
#endif /* __APP_FREERTOS_H */
