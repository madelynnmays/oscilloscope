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
