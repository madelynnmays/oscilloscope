/*
 * Formatter.c
 *
 *  Created on: Oct 7, 2026
 *      Author: Madelynn
 */

//nick
#include "Formatter.h"

const uint8_t Array_setup[13] = {0x40, 0xA1, 0xC0, 0xA4, 0xA6, 0xA2, 0x2F, 0x27, 0x81, 0x10, 0xFA, 0x90, 0xAF};
// jargon code for spi
void Spi_init(){
	GPIOA->ODR &= ~GPIO_PIN_5;
	for (uint8_t i = 0; i<12; i++){
		LL_SPI_TransmitData8(SPI1, Array_setup[i]);
	}
	for (uint32_t j = 0; j<123456; j++){
		if(!LL_SPI_IsActiveFlag_BSY(SPI1)){break;}
	}
	GPIOA->ODR |= GPIO_PIN_5;
}

void Spi_Formant_Send(int x, int y){

	GPIOA->ODR &= ~GPIO_PIN_5;

	//page? y cord/8 to get the page
	// then for the bit is y%8

	//frame buffer?
	//[page][x]
	//some bullshit ig idk anymore?

	for (uint32_t j = 0; j<123456; j++){
		if(!LL_SPI_IsActiveFlag_BSY(SPI1)){break;}
	}

	GPIOA->ODR |= GPIO_PIN_5;
}
