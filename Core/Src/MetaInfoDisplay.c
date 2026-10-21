/*
 * MetaInfoDisplay.c
 *
 *  Created on: Oct 7, 2026
 *      Author: Madelynn
 */

#include "MetaInfoDisplay.h"

void DisplayVoltageValue(int16_t num)
{

	/* TODO */
	return;
}

void DisplayCursorValue(int16_t num)
{
	/* TODO */
	return;
}

void DisplayCursor2Value(int16_t num)
{
	/* TODO */
	return;
}

void initMetaInfo()
{
	//taken straight from the manual
	MetaInfoBus->ODR &= ~MetaInfoClockMask; //clock low
	for (int i = 0; i<100;i++){;}
	//TODO
	//change to 40ms
	sendMetaInfoBus(0x30); //wake up command
	for (int i = 0; i<100;i++){;}
	//TODO
	//change to 5ms
	sendMetaInfoBus(0x30); //wake up command 2
	for (int i = 0; i<100;i++){;}
	//TODO
	//change to 160us
	sendMetaInfoBus(0x30); //wake up command 3
	for (int i = 0; i<100;i++){;}
	//TODO
	//change to 160us
	sendMetaInfoBus(0x38); // 8 bit input, 2 line
	sendMetaInfoBus(0x10); // set cursor
	sendMetaInfoBus(0x0c); // display on, cursor on
	sendMetaInfoBus(0x06); // entry mode set
	return;
}

void sendMetaInfoBus(uint8_t data)
{

	MetaInfoBus->ODR = data; //data on bus
	MetaInfoBus->ODR |= MetaInfoRSMask; //set RS high
	MetaInfoBus->ODR &= ~(MetaInfoRWMask); //set RW low
	MetaInfoBus->ODR |= MetaInfoClockMask; //set clock high
	for (int i = 0; i<100;i++){;} //wait for a second
	//TODO
	//REMOVE MAGIC NUMBER and make 300ns or longer
	MetaInfoBus->ODR &= ~MetaInfoClockMask; //clock low

	return;
}
