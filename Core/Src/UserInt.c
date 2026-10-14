/*
 * UserInt.c
 *
 *  Created on: Oct 7, 2026
 *      Author: Madelynn
 */


void ButtonDebounce(){

	/* TODO */
	return;
}

void KnobDeboucne(){

	/* TODO */
	return;
}
/*
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
		GPIOA->ODR &= ~(1<<9); //green
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
}*/

/*
 * 	  todo
	  btnHandler(&encoderA);
	  btnHandler(&encoderB);

	  	if (encoderA.btnState == FALL){
	  		if (encoderB.btnState == HIGH){
	  			count++;
	  		} else {
	  			count--;
	  		}
	  	}

	  	btnHandler(&btnUp);
	  	btnHandler(&btnUp);
	  	if((btnUp.btnState == HIGH) & (btnDown.btnState == RISE))
	  	{
	  	  count++;
	  	}
	  	else if ((btnUp.btnState == LOW) & (btnDown.btnState == RISE))
	  	{
	  	  count--;
	  	}
	  	count = roundCount(count);
	  	updateLED(count);
	  	for (uint16_t i = 0; i< delay; i++){;}
 *
 *
 *
 *	CN10.4 (PC6) ==> Green Button increment
  	  CN10.19 (PC7) ==> Red Button Decrement
  	  CN10.21 (PA9) ==> Red LED 1's
  	  CN10.23 (PA8) ==> Green LED 2's
  	int8_t count = 1;
  	struct btn btnUp = {HIGH,6, GPIOC};
  	struct btn btnDown = {HIGH,7, GPIOC};

  	struct btn encoderA = {HIGH, 6, GPIOC};
  	struct btn encoderB = {HIGH, 7, GPIOC};
  	const uint16_t delay = 2000;
 *
 *
 * */
