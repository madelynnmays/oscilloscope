/*
 * Trigger.c
 *
 *  Created on: Oct 7, 2026
 *      Author: Madelynn
 */


#include "Trigger.h"


uint16_t triggerDetect(uint16_t result_previous, uint32_t triggerLevel, enum triggerEdge edge)
{

	uint16_t result_current;

	//result previous is reading n-1
	//result current is reading n
	if (osMessageQueueGet(voltReadingTaskHandle, &result_current, 0, 100) == osOK)
	{

		if(result_current > result_previous && edge == RISE)
		{
			if(result_current > triggerLevel && triggerLevel > result_previous)
			{
				//TODO
				//raise a semaphore
			}
		}
		else if(result_current < result_previous && edge == FALL)
		{
			if(result_current < triggerLevel && triggerLevel < result_previous)
			{
				//TODO
				//raise a semaphore
			}
		}




		return result_current; //to be fed back in the next time we call this
		//will be cleared to 0 outside this func should this be a fresh trigger check
	}

}
