/*
 * UserInt.h
 *
 *  Created on: Oct 7, 2026
 *      Author: Madelynn
 */


//nick

#ifndef INC_USERINT_H_
#define INC_USERINT_H_

#include "main.h"

enum buttonStates {HIGH,LOW,LBD,HBD,RISE,FALL};
struct btn
{
	enum buttonStates btnState;
	uint8_t pin;
	GPIO_TypeDef *pinGroup;
};
uint8_t btnHandler(struct btn *btn);

void asciiConverter(uint16_t number, uint8_t* digit1, uint8_t* digit2, uint8_t* digit3, uint8_t* digit4);


#endif /* INC_USERINT_H_ */
