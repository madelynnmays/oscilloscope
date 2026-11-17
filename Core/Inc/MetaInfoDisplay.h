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
#include "app_freertos.h"


#define MetaInfoBus GPIOB
#define MetaInfoClockMask (1<<10)
#define MetaInfoRSMask (1<<9)
#define MetaInfoRWMask (1<<8)

void sendMetaInfoCommand(uint8_t data);
void sendMetaInfoWrite(uint8_t data);

void initMetaInfo();
void updateMetaDisplay(uint8_t topLine[16], uint8_t bottomLine[16]);

#endif /* INC_METAINFODISPLAY_H_ */
