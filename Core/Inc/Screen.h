/*
 * Screen.h
 *
 *  Created on: Oct 7, 2026
 *      Author: Madelynn
 */

//nick
#ifndef INC_SCREEN_H_
#define INC_SCREEN_H_

#include "app_freertos.h"
#include "main.h"


void PlotDataPoints(uint8_t plotpoint);
void Spi_init(void);
void Adjust_adc_values(void);
void Spi_Format_Region(uint8_t startPage, uint8_t endPage, uint8_t startCol,  uint8_t endCol, uint8_t fill);


#endif /* INC_SCREEN_H_ */
