/*
 * Trigger.h
 *
 *  Created on: Oct 7, 2026
 *      Author: Madelynn
 */


//madelynn

//UserInt handles the actual trigger level value getting.

//Will determine whether it's time to trigger, and center the display about that trigger level
//relies on VoltMeasure

//STRETCH: output "trigger out of bound" error or similar
//if the trigger level is outside of the input
#ifndef INC_TRIGGER_H_
#define INC_TRIGGER_H_


#include "main.h"
#include "app_freertos.h"

enum triggerEdge {RISING,FALLING};

uint16_t triggerDetect(uint16_t result_previous, uint32_t triggerLevel, enum triggerEdge edge);
// does trigger level lie between input n and n+1? if n+1 > n, then the edge is rising, else falling

void triggerIndexParser(circ_bbuf_t *cbuff_results);











#endif /* INC_TRIGGER_H_ */
