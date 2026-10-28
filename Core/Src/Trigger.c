/*
 * Trigger.c
 *
 *  Created on: Oct 7, 2026
 *      Author: Madelynn
 */


#include "Trigger.h"


uint16_t triggerDetect(uint16_t result_previous, uint16_t result_current, uint32_t triggerLevel, enum triggerEdge edge)
{



	//result previous is reading n-1
	//result current is reading n



		if(result_current > result_previous && edge == RISING)
		{
			if(result_current > triggerLevel && triggerLevel > result_previous)
			{
				//TODO
				//raise a semaphore
			}
		}
		if(result_current < result_previous && edge == FALLING)
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


void triggerIndexParser(circ_bbuf_t *cbuff_results, enum triggerEdge edge, uint32_t triggerLevel)
{
	uint16_t priorResult = cbuff_results->buffer[0];
	for(int j = 1; j < cbuff_results->maxlen; j++)
	{
		priorResult = triggerDetect(priorResult, cbuff_results->buffer[i],triggerLevel, edge);
		//todo semaphore comparison

	}

}
