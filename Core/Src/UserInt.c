/*
 * UserInt.c
 *
 *  Created on: Oct 7, 2026
 *      Author: Madelynn
 */

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
