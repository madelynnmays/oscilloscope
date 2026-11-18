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

uint16_t scale_period(){
	uint16_t scalex;
	uint16_t Period_enc_value;
	osMessageQueueGet(horizontalScaleHandle, &Period_enc_value, NULL, 0);
	scalex = 100/Period_enc_value;
	return scalex;
}



