/*
 * MetaInfoDisplay.h
 *
 *  Created on: Oct 7, 2026
 *      Author: Madelynn
 */

//madelynn
#ifndef INC_METAINFODISPLAY_H_
#define INC_METAINFODISPLAY_H_

#include "main.h"


#define MetaInfoBus GPIOB
#define MetaInfoClockMask (1<<10)
#define MetaInfoRSMask (1<<9)
#define MetaInfoRWMask (1<<8)
// filler names for when we get an idea of what values will be displayed.

void DisplayVoltageValue(int16_t num);// could display voltage

void DisplayCursorValue(int16_t num);// could be the cursor value

void DisplayCursor2Value(int16_t num);// could be another cursor

void sendMetaInfoCommand(uint8_t data);
void sendMetaInfoWrite(uint8_t data);

void initMetaInfo();
void updateMetaDisplay(uint8_t topLine[16], uint8_t bottomLine[16]);

#endif /* INC_METAINFODISPLAY_H_ */
