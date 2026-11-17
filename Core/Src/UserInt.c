/*
 * UserInt.c
 *
 *  Created on: Oct 7, 2026
 *      Author: Madelynn
 */
//nick
#include "UserInt.h"


uint8_t btnHandler(struct btn *btn)
{

	switch(btn->btnState)
	{
	case HIGH:
		if (btn->pinGroup->IDR & (1<<(btn->pin))) {;}
		else {btn->btnState = HBD;}
		break;
	case HBD:
		if (btn->pinGroup->IDR & (1<<(btn->pin))) {btn->btnState = HIGH;}
		else {btn->btnState = FALL;}
		break;
	case FALL:
		btn->btnState = LOW;
		break;
	case LOW:
		if (btn->pinGroup->IDR & (1<<(btn->pin))) {btn->btnState = LBD;;}
		break;
	case LBD:
		if (btn->pinGroup->IDR & (1<<(btn->pin))) {btn->btnState = RISE;}
		else {btn->btnState = LOW;}
		break;
	case RISE:
		btn->btnState = HIGH;
		break;
	}
	return(btn->btnState == FALL);
}

void asciiConverter(uint16_t number, uint8_t* digit1, uint8_t* digit2, uint8_t* digit3, uint8_t* digit4)
{
		*digit1 = (number % 10) + '0';
	    *digit2 = ((number / 10) % 10) + '0';
	    *digit3 = ((number / 100) % 10) + '0';
	    *digit4 = ((number / 1000) % 10) + '0';
	return;


}

