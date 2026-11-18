/*
 * MetaInfoDisplay.c
 *
 *  Created on: Oct 7, 2026
 *      Author: Madelynn
 */

#include "MetaInfoDisplay.h"

void initMetaInfo()
{
	//taken straight from the manual
	MetaInfoBus->ODR &= ~MetaInfoClockMask; //clock low
	for (int i = 0; i<10000;i++){;}
	osDelay(40);

	sendMetaInfoCommand(0x30); //wake up command
	osDelay(5);
	for (int i = 0; i<10000;i++){;}

	sendMetaInfoCommand(0x30); //wake up command 2
	osDelay(5);
	for (int i = 0; i<10000;i++){;}	//

	sendMetaInfoCommand(0x30); //wake up command 3
	osDelay(5);
	for (int i = 0; i<10000;i++){;}

	sendMetaInfoCommand(0x38); // 8 bit input, 2 line
	osDelay(5);
	sendMetaInfoCommand(0x10); // set cursor
	osDelay(5);
	sendMetaInfoCommand(0x0f); // display on, cursor on, blinky on
	osDelay(5);
	sendMetaInfoCommand(0x06); // entry mode set
	osDelay(5);
	sendMetaInfoCommand(0x01); // clear display
	osDelay(5);
	for (int i = 0; i<10000;i++){;}
	osDelay(5);
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
	for (int i = 0; i<10000;i++){;} //wait for a second
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
	for (int i = 0; i<10000;i++){;} //wait for a second
	//TODO
	//REMOVE MAGIC NUMBER and make 300ns or longer
	MetaInfoBus->ODR &= ~MetaInfoClockMask; //clock low
	for (int i = 0; i<10000;i++){;}

	return;
}
void updateMetaDisplay(uint8_t topLine[16], uint8_t bottomLine[16])
{
	sendMetaInfoCommand(0x01); // clear display
	sendMetaInfoCommand(0x02); // return home
	for(int i=0;i<16;i++)
	{
	  sendMetaInfoWrite(topLine[i]);
	}
	sendMetaInfoCommand(0xC0); // go to next line
	for(int j=0;j<16;j++)
	{
	  sendMetaInfoWrite(bottomLine[j]);
	}
	return;

}
