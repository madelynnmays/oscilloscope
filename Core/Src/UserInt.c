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

void updateLED(uint8_t count)
{
	switch(count)
	{
	case 1: //01
		GPIOA->ODR &= ~(1<<8); //green
		GPIOA->ODR |= (1<<9); //red
		break;
	case 2: //10
		GPIOA->ODR |= (1<<8); //red
		GPIOA->ODR &= ~(1<<9);
		break;
	case 3: //11
		GPIOA->ODR |= (1<<9); //red
		GPIOA->ODR |= (1<<8); //green
		break;
	case 0: //0
		GPIOA->ODR &= ~(1<<9); //red
		GPIOA->ODR &= ~(1<<8); //green
		break;
	default:
		GPIOA->ODR &= ~(1<<9); //red
		GPIOA->ODR &= ~(1<<8); //green
	}
	return;

}

int8_t roundCount(int8_t count)
{
	if (count < 0)
	{
		return 0;
	}
	else if (count > 3)
	{
		return 3;
	}
	else
	{
		return count;
	}
}
