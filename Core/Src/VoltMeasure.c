/*
 * VoltMeasure.c
 *
 *  Created on: Oct 7, 2026
 *      Author: Madelynn
 */


#include "VoltMeasure.h"
#include "app_freertos.h"



uint16_t convertADCtomv(uint16_t ADCResult)
{
	const float resolutionADC = 0.8; //approx 0.8mv per tick
	return (uint16_t)(ADCResult * (resolutionADC));
	// also not sure if it just handles negative numbers
}
uint16_t readADC()
{
	//this func is too long so i shall rename it
	return LL_ADC_REG_ReadConversionData12(ADC1);
}


//source: https://embedjournal.com/implementing-circular-buffer-embedded-c/
int circ_bbuf_push(circ_bbuf_t *c, uint16_t data)
{
    int next;

    next = c->head + 1;  // next is where head will point to after this write.
    if (next >= c->maxlen)
    {
    	next = 0;
    }

    //change from src
	//only throw error when overwritable is false
	//else just let the head go on
    if (next == c->tail)  // if the head + 1 == tail, circular buffer is full
    {
    	if (c->overwritable == 0)
		{
		return -1;
		}
    	else //also advance the tail, so that the tail points to the oldest data
    	{
    		c->tail++;
			if (c->tail >= c->maxlen)
			{
				c->tail = 0;
			}
			c->full = 1; //if the head has overwritten data, flag as full
    	}
    }


    c->buffer[c->head] = data;  // Load data and then move
    c->head = next;             // head to next data offset.
    return 0;  // return success to indicate successful push.
}

int circ_bbuf_pop(circ_bbuf_t *c, uint16_t *data)
{
    int next;

    if (c->head == c->tail)
    {
    	return -1;// if the head == tail, we don't have any data
    }


    next = c->tail + 1;  // next is where tail will point to after this read.
    if(next >= c->maxlen)
        next = 0;

    *data = c->buffer[c->tail];  // Read data and then move
    c->tail = next;              // tail to next offset.
    return 0;  // return success to indicate successful push.
}

uint16_t calcPeriod(uint16_t timescale)
{
	uint16_t reload = (2000*timescale)/99 - 1;
			// div by 99 bc there are 100-1 pixels on the screen
			//mult by 2000 because the powers on mHz and tenths of ms cancel to leave that
	return reload;
}

void changeTIM16Period(uint16_t reloadVal)
{
	 LL_TIM_DisableIT_UPDATE(TIM16);
	LL_TIM_DisableCounter(TIM16);


	LL_TIM_SetAutoReload(TIM16, reloadVal);


	LL_TIM_GenerateEvent_UPDATE(TIM16);
	LL_TIM_SetCounter(TIM16, 0);
	LL_TIM_ClearFlag_UPDATE(TIM16);

	LL_TIM_EnableIT_UPDATE(TIM16);
	LL_TIM_EnableCounter(TIM16);
	return;
}
