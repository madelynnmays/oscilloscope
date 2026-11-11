/*
 * Screen.c
 *
 *  Created on: Oct 7, 2026
 *      Author: Madelynn
 */
//nick
#include "Screen.h"
//spi init and screen cmd are useful
//spi formate region was for testing display and had more value before.
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
void PlotDataPoints(uint8_t plotpoint){

}
