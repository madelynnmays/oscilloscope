/*
 * Trigger.c
 *
 *  Created on: Oct 7, 2026
 *      Author: Madelynn
 */


#include "Trigger.h"


uint16_t triggerDetect(uint16_t result_previous, uint16_t result_current, uint32_t triggerLevel, enum triggerEdge edge)
{


	osSemaphoreAcquire(triggerHappenedHandle, osWaitForever);
	osSemaphoreAcquire(stopCheckingTriggerHandle, osWaitForever);
	//result previous is reading n-1
	//result current is reading n



		if(result_current > result_previous && edge == RISING)
		{
			if(result_current > triggerLevel && triggerLevel > result_previous)
			{
				osSemaphoreRelease(semaphore_id)(triggerHappenedHandle, osWaitForever);
				osSemaphoreRelease(semaphore_id)(stopCheckingTriggerHandle, osWaitForever);
			}
		}
		if(result_current < result_previous && edge == FALLING)
		{
			if(result_current < triggerLevel && triggerLevel < result_previous)
			{
				osSemaphoreRelease(triggerHappenedHandle, osWaitForever);
				osSemaphoreRelease(stopCheckingTriggerHandle, osWaitForever);
			}
		}

		return result_current; //to be fed back in the next time we call this
		//will be cleared to 0 outside this func should this be a fresh trigger check



}


void triggerIndexParser(circ_bbuf_t *cbuff_results, enum triggerEdge edge, uint32_t triggerLevel)
{
	uint16_t priorResult = cbuff_results->buffer[0];
	for(uint8_t j = 1; j < cbuff_results->maxlen; j++)
	{
		priorResult = triggerDetect(priorResult, cbuff_results->buffer[i],triggerLevel, edge);
		//todo semaphore comparison
		if(osSemaphoreAcquire(stopCheckingTriggerHandle, 15) == osOK)
		{
			uint8_t triggerPosition = j;
			osMessageQueuePut(triggerPositionHandle, &triggerPosition, 0, osWaitForever);
			break;
		}

	}

}
