/*
 * VoltMeasure.c
 *
 *  Created on: Oct 7, 2026
 *      Author: Madelynn
 */


#include "VoltMeasure.h"

const uint16_t resolutionADC = 1234; //idk what it actually is

uint16_t convertADCtomv(uint16_t ADCResult)
{

	return ADCResult * resolutionADC;
	// also not sure if it just handles negative numbers
}
uint16_t readADC(void)
{
	//this func is too long so i shall rename it
	return LL_ADC_REG_ReadConversionData12(ADC1);
}


//source: https://embedjournal.com/implementing-circular-buffer-embedded-c/
int circ_bbuf_push(circ_bbuf_t *c, uint8_t data)
{
    int next;

    next = c->head + 1;  // next is where head will point to after this write.
    if (next >= c->maxlen)
        next = 0;

    if (next == c->tail)  // if the head + 1 == tail, circular buffer is full
        return -1;

    c->buffer[c->head] = data;  // Load data and then move
    c->head = next;             // head to next data offset.
    return 0;  // return success to indicate successful push.
}

int circ_bbuf_pop(circ_bbuf_t *c, uint8_t *data)
{
    int next;

    if (c->head == c->tail)  // if the head == tail, we don't have any data
        return -1;

    next = c->tail + 1;  // next is where tail will point to after this read.
    if(next >= c->maxlen)
        next = 0;

    *data = c->buffer[c->tail];  // Read data and then move
    c->tail = next;              // tail to next offset.
    return 0;  // return success to indicate successful push.
}


