/*
 * Screen.c
 *
 *  Created on: Oct 7, 2026
 *      Author: Madelynn
 */

#include "Screen.h"
//spi init and screen cmd are useful
//spi formate region was for testing display and had more value before.
static const uint8_t sineWave[64] = {
	  128, 140, 152, 165, 176, 188, 198, 208,
	  218, 226, 234, 240, 245, 250, 253, 254,
	  255, 254, 253, 250, 245, 240, 234, 226,
	  218, 208, 198, 188, 176, 165, 152, 140,
	  128, 115, 103,  90,  79,  67,  57,  47,
	   37,  29,  21,  15,  10,   5,   2,   1,
	    0,   1,   2,   5,  10,  15,  21,  29,
	   37,  47,  57,  67,  79,  90, 103, 115
	}; //test print

void Spi_init(void)
{
	LL_SPI_Enable(SPI1);
	GPIOA->ODR |= GPIO_PIN_4; //set reset high
	uint8_t Array_setup[] = {0x40, 0xa1, 0xc0, 0xa4, 0xa6, 0xa2, 0x2f, 0x27, 0x81, 0x10, 0xfa, 0x90, 0xaf}; //intialize code
	GPIOA->ODR |= GPIO_PIN_5;
	GPIOA->ODR |= GPIO_PIN_8;
	osDelay(50);
	GPIOA->ODR &= ~GPIO_PIN_8; // D/C low: command mode
	for(int i=0; i < 13; i++){
		GPIOA->ODR &= ~GPIO_PIN_5; //CS low
		LL_SPI_TransmitData8(SPI1, Array_setup[i]);
		osDelay(5);
		GPIOA->ODR |= GPIO_PIN_5;
	}
	GPIOA->ODR |= GPIO_PIN_8;
}

void screen_cmd(uint8_t byte)
{
    GPIOA->ODR &= ~GPIO_PIN_8;               // D/C low = command
    GPIOA->ODR &= ~GPIO_PIN_5;               // CS low
    while (!LL_SPI_IsActiveFlag_TXE(SPI1));
    LL_SPI_TransmitData8(SPI1, byte);
    while (!LL_SPI_IsActiveFlag_TXE(SPI1));
    while (LL_SPI_IsActiveFlag_BSY(SPI1));
    GPIOA->ODR |= GPIO_PIN_5;                // CS high
}

void Spi_Format_Region(uint8_t startPage, uint8_t endPage, uint8_t startCol,  uint8_t endCol, uint8_t fill)
{
    for (uint8_t page = startPage; page <= endPage; page++) {
        screen_cmd(0xB0 + page);
        screen_cmd(0x10 | (startCol >> 4));
        screen_cmd(0x00 | (startCol & 0x0F));

        GPIOA->ODR |= GPIO_PIN_8;
        GPIOA->ODR &= ~GPIO_PIN_5;
        for (uint8_t col = startCol; col <= endCol; col++) {
            while (!LL_SPI_IsActiveFlag_TXE(SPI1));
            LL_SPI_TransmitData8(SPI1, fill);
        }
        while (!LL_SPI_IsActiveFlag_TXE(SPI1));
        while (LL_SPI_IsActiveFlag_BSY(SPI1));
        GPIOA->ODR |= GPIO_PIN_5;
    }
}
