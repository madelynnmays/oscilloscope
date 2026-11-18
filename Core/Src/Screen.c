/*
 * Screen.c
 *
 *  Created on: Oct 7, 2026
 *      Author: Madelynn
 */
//nick
#include "Screen.h"
#include "Formatter.h"
//spi init and screen cmd are useful
//spi format region was for testing display and had more value before.
void Spi_init(void)
{
	LL_SPI_Enable(SPI1);
	GPIOA->ODR &= ~GPIO_PIN_4;
	osDelay(3);
	GPIOA->ODR |= GPIO_PIN_4; //set reset high
	uint8_t Array_setup[] = {0x40, 0xa1, 0xc0, 0xa4, 0xa6, 0xa2, 0x2f, 0x27, 0x81, 0x10, 0xfa, 0x90, 0xaf}; //intialize code
	GPIOA->ODR |= GPIO_PIN_5;
	GPIOA->ODR |= GPIO_PIN_8;
	osDelay(50);
	GPIOA->ODR &= ~GPIO_PIN_8; // D/C low: command mode
	for(int i=0; i < 13; i++){
		GPIOA->ODR &= ~GPIO_PIN_5; //CS low
	    osDelay(5);
	    LL_SPI_TransmitData8(SPI1, Array_setup[i]);

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

        GPIOA->ODR |= GPIO_PIN_8; //data
        GPIOA->ODR &= ~GPIO_PIN_5; //cs low
        for (uint8_t col = startCol; col <= endCol; col++) {
            while (!LL_SPI_IsActiveFlag_TXE(SPI1));
            LL_SPI_TransmitData8(SPI1, fill);
        }
        while (!LL_SPI_IsActiveFlag_TXE(SPI1));
        while (LL_SPI_IsActiveFlag_BSY(SPI1));
        GPIOA->ODR |= GPIO_PIN_5;
    }
}
void PlotDataPoints(uint16_t *y)
{
	uint16_t scale_y = scale_amplitude();

	for (uint16_t col = 0; col < 100; col++) {

		int32_t row = 63 - ((int32_t)y[col] * 63) / scale_y;

		if (row < 0)  row = 0;
		if (row > 63) row = 63;

		uint8_t pageformat = row / 8;
		uint8_t pixel = 1 << (row % 8);

		screen_cmd(0xB0 + pageformat);
		screen_cmd(0x00 | (col & 0x0F));
		screen_cmd(0x10 | (col >> 4));

		GPIOA->ODR |= GPIO_PIN_8;                         // data
		GPIOA->ODR &= ~GPIO_PIN_5;                        // cs low
		while (!LL_SPI_IsActiveFlag_TXE(SPI1));
		LL_SPI_TransmitData8(SPI1, pixel);
		while (!LL_SPI_IsActiveFlag_TXE(SPI1));
		while (LL_SPI_IsActiveFlag_BSY(SPI1));
		GPIOA->ODR |= GPIO_PIN_5;                         // cs high
	}
	return;
}

