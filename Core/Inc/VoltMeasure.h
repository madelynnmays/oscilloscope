/*
 * VoltMeasure.h
 *
 *  Created on: Oct 7, 2026
 *      Author: Madelynn
 */

//madelynn

//ADC controls
//formats into (time, voltage)
#ifndef INC_VOLTMEASURE_H_
#define INC_VOLTMEASURE_H_

#include "main.h"

//ISR to be added

extern const uint16_t resolutionADC;


uint16_t convertADCtomv(uint16_t ADCResult);










#endif /* INC_VOLTMEASURE_H_ */
