/*
 * Formatter.c
 *
 *  Created on: Oct 7, 2026
 *      Author: Madelynn
 */

//nick
#include "Formatter.h"

uint16_t scale_amplitude(){
	uint16_t scaley;
	uint16_t amp_enc_value = osMessageQueueGet(horizontalScaleHandle, &scaley, 0, osWaitForever);
	scaley = 64/amp_enc_value;
	return scaley;
}
uint16_t scale_period(){
	uint16_t scalex;
	uint16_t Period_enc_value = osMessageQueueGet(verticalScaleHandle, &scalex, 0, osWaitForever);
	scalex = 100/Period_enc_value;
	return scalex;
}

