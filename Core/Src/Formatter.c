/*
 * Formatter.c
 *
 *  Created on: Oct 7, 2026
 *      Author: Madelynn
 */

//nick
#include "Formatter.h"

uint16_t scale_amplitude(void)
{
    static uint16_t last = 100;          // mV per div
    uint16_t v;
    while (osMessageQueueGet(verticalScaleHandle, &v, NULL, 0) == osOK) {
        last = v;
    }
    if (last == 0) last = 100;
    return last;
}
uint16_t scale_xcheck(uint16_t scale_x, uint16_t prev_x){
	  if (scale_x != prev_x) {
	      osMessageQueueReset(horizontalScaleHandle);
	      osMessageQueuePut(horizontalScaleHandle, &scale_x, 0, 0);
	      prev_x = scale_x;
	  }
	  return prev_x;
}

uint16_t scale_yCheck(uint16_t scale_y, uint16_t prev_y){
	  if (scale_y != prev_y) {
	      osMessageQueueReset(verticalScaleHandle);
	      osMessageQueuePut(verticalScaleHandle, &scale_y, 0, 0);
	      prev_y = scale_y;
	  }
	  return prev_y;
}

uint16_t Trigger_valCheck(uint16_t trigger_val, uint16_t prev_t){
	  if (trigger_val != prev_t) {
	      osMessageQueueReset(triggerLevelHandle);
	      osMessageQueuePut(triggerLevelHandle, &trigger_val, 0, 0);
	      prev_t = trigger_val;
	  }
	  return prev_t;
}



