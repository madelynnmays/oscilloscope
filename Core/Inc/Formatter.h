/*
 * Formatter.h
 *
 *  Created on: Oct 7, 2026
 *      Author: Madelynn
 */


//

//nicholas


#ifndef INC_FORMATTER_H_
#define INC_FORMATTER_H_

#include "app_freertos.h"
#include "main.h"

uint16_t scale_amplitude();
uint8_t scaleWave(uint16_t value, uint16_t screenTop);

uint16_t scale_xcheck(uint16_t scale_x, uint16_t prev_x);

uint16_t scale_yCheck(uint16_t scale_y, uint16_t prev_y);

uint16_t Trigger_valCheck(uint16_t trigger_val, uint16_t prev_t);

#endif /* INC_FORMATTER_H_ */
