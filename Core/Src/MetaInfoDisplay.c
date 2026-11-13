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
	for (int i = 0; i<10000;i++){;}	//TODO
	//change to 40ms
	sendMetaInfoCommand(0x30); //wake up command
	for (int i = 0; i<10000;i++){;}	//TODO
	//change to 5ms
	sendMetaInfoCommand(0x30); //wake up command 2
	for (int i = 0; i<10000;i++){;}	//TODO
	//change to 160us
	sendMetaInfoCommand(0x30); //wake up command 3
	for (int i = 0; i<10000;i++){;}	//TODO
	//change to 160us
	sendMetaInfoCommand(0x38); // 8 bit input, 2 line
	sendMetaInfoCommand(0x10); // set cursor
	sendMetaInfoCommand(0x0f); // display on, cursor on, blinky on
	sendMetaInfoCommand(0x06); // entry mode set
	sendMetaInfoCommand(0x01); // clear display
	for (int i = 0; i<10000;i++){;}
	sendMetaInfoCommand(0x02); // return home
	for (int i = 0; i<10000;i++){;}



	return;
}

void sendMetaInfoCommand(uint8_t data)
{

	MetaInfoBus->ODR = data; //data on bus
	MetaInfoBus->ODR &= ~MetaInfoRSMask; //set RS low
	MetaInfoBus->ODR &= ~(MetaInfoRWMask); //set RW low
	MetaInfoBus->ODR |= MetaInfoClockMask; //set clock high
	for (int i = 0; i<1000;i++){;} //wait for a second
	//TODO
	//REMOVE MAGIC NUMBER and make 300ns or longer
	MetaInfoBus->ODR &= ~MetaInfoClockMask; //clock low
	for (int i = 0; i<10000;i++){;}
	return;
}
void sendMetaInfoWrite(uint8_t data)
{

	MetaInfoBus->ODR = data; //data on bus
	MetaInfoBus->ODR |= MetaInfoRSMask; //set RS high
	MetaInfoBus->ODR &= ~(MetaInfoRWMask); //set RW low
	MetaInfoBus->ODR |= MetaInfoClockMask; //set clock high
	for (int i = 0; i<100;i++){;} //wait for a second
	//TODO
	//REMOVE MAGIC NUMBER and make 300ns or longer
	MetaInfoBus->ODR &= ~MetaInfoClockMask; //clock low
	for (int i = 0; i<10000;i++){;}

	return;
}
