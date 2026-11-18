/*
 * Screen.c
 *
 *  Created on: Oct 7, 2026
 *      Author: Madelynn
 */
//nick
#include "Screen.h"
#include "Formatter.h"
#include <string.h>
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
static uint8_t fb[8][100];

void PlotDataPoints(uint16_t *y)
{
	uint16_t scale_y = scale_amplitude();
	if (scale_y == 0) scale_y = 1;

	memset(fb, 0, sizeof(fb));                       //ai suggestion from here\/

	int32_t prevRow = 0;
	for (uint16_t col = 0; col < 100; col++) {
		int32_t row = 63 - ((int32_t)y[col] * 63) / scale_y;
		if (row < 0)  row = 0;
		if (row > 63) row = 63;

		// connect to the previous column's row
		int32_t from = (col == 0) ? row : prevRow;
		int32_t lo = (from < row) ? from : row;
		int32_t hi = (from < row) ? row : from;
		for (int32_t r = lo; r <= hi; r++) {
			fb[r / 8][col] |= (1u << (r % 8));
		}
		prevRow = row;
	}                                             //to here                  /\

	for (uint8_t page = 0; page < 8; page++) {
		screen_cmd(0xB0 + page);
		screen_cmd(0x00);
		screen_cmd(0x10);

		GPIOA->ODR |= GPIO_PIN_8;                    // data
		GPIOA->ODR &= ~GPIO_PIN_5;                   // CS low
		for (uint16_t col = 0; col < 100; col++) {
			while (!LL_SPI_IsActiveFlag_TXE(SPI1));
			LL_SPI_TransmitData8(SPI1, fb[page][col]);
		}
		while (!LL_SPI_IsActiveFlag_TXE(SPI1));
		while (LL_SPI_IsActiveFlag_BSY(SPI1));
		GPIOA->ODR |= GPIO_PIN_5;                    // CS high
	}
}



