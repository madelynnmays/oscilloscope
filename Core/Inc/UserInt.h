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

#endif /* INC_USERINT_H_ */
