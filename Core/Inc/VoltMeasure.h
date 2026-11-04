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
#include <stdbool.h>

//ISR to be added

extern const float resolutionADC;

typedef struct {
    uint16_t * const buffer;
    int head;
    int tail;
    const int maxlen;
    uint8_t overwritable;
} circ_bbuf_t;
int circ_bbuf_push(circ_bbuf_t *c, uint16_t data);
int circ_bbuf_pop(circ_bbuf_t *c, uint16_t *data);
//source: https://embedjournal.com/implementing-circular-buffer-embedded-c/

uint16_t convertADCtomv(uint16_t ADCResult);
uint16_t readADC();









#endif /* INC_VOLTMEASURE_H_ */
