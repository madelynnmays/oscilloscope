/*
 * Formatter.c
 *
 *  Created on: Oct 7, 2026
 *      Author: Madelynn
 */

//nick
#include "Formatter.h"

// jargon code for spi
void Spi_init(void)
{
	GPIOA->ODR |= GPIO_PIN_4;
	uint8_t Array_setup[] = {0x40, 0xa1, 0xc0, 0xa4, 0xa6, 0xa2, 0x2f, 0x27, 0x81, 0x10, 0xfa, 0x90, 0xaf};
	GPIOA->ODR |= GPIO_PIN_5;
	GPIOA->ODR |= GPIO_PIN_8;
	osDelay(200);

	GPIOA->ODR &= ~GPIO_PIN_8; // D/C low: command mode
	for(int i=0; i < 13; i++){
		GPIOA->ODR &= ~GPIO_PIN_5; //CS low
		LL_SPI_TransmitData8(SPI1, Array_setup[i]);
		osDelay(200);
		GPIOA->ODR |= GPIO_PIN_5;
	}
	GPIOA->ODR |= GPIO_PIN_8;
}

void Spi_Format_Send(/*int x, int y*/){

    for (uint8_t page = 0; page < 8; page++) {

        // Step A: Set Address Coordinates
        GPIOA->ODR &= ~GPIO_PIN_8; // CD Low -> Command Mode
        GPIOA->ODR &= ~GPIO_PIN_5; // CS Low

        while (!LL_SPI_IsActiveFlag_TXE(SPI1));
        LL_SPI_TransmitData8(SPI1, 0xB0 + page); // Set Current Page (0xB0 to 0xB7)
        osDelay(1000);

        GPIOA->ODR |= GPIO_PIN_8;
        GPIOA->ODR |= GPIO_PIN_5;
        GPIOA->ODR &= ~GPIO_PIN_5; // CS Low
        GPIOA->ODR &= ~GPIO_PIN_8;

        while (!LL_SPI_IsActiveFlag_TXE(SPI1));
        LL_SPI_TransmitData8(SPI1, 0x10);        // Column High Nibble = 0
        osDelay(1000);

        GPIOA->ODR |= GPIO_PIN_8;
        GPIOA->ODR |= GPIO_PIN_5;
        GPIOA->ODR &= ~GPIO_PIN_5;
        GPIOA->ODR &= ~GPIO_PIN_8;

        while (!LL_SPI_IsActiveFlag_TXE(SPI1));
        LL_SPI_TransmitData8(SPI1, 0x00);        // Column Low Nibble = 0
        osDelay(1000);

        GPIOA->ODR |= GPIO_PIN_8;
        GPIOA->ODR |= GPIO_PIN_5;
        GPIOA->ODR &= ~GPIO_PIN_5;
        GPIOA->ODR &= ~GPIO_PIN_8;

        while (LL_SPI_IsActiveFlag_BSY(SPI1));   // Wait for address commands to land
        GPIOA->ODR |= GPIO_PIN_5;                // CS High
        // Step B: Blast Raw Solid Pixels across all 102 horizontal points
        GPIOA->ODR |= GPIO_PIN_8;  // CD High -> Data Mode

        osDelay(1000);

        for (uint8_t col = 0; col < 120; col++) {
        	GPIOA->ODR &= ~GPIO_PIN_5; // CS Low
            while (!LL_SPI_IsActiveFlag_TXE(SPI1));
            LL_SPI_TransmitData8(SPI1, 0x0f);    // 0xFF forces all 8 vertical pixels ON
            osDelay(50);
            GPIOA->ODR |= GPIO_PIN_5;

        }

        while (LL_SPI_IsActiveFlag_BSY(SPI1));   // Wait for page row transfer complete
        GPIOA->ODR |= GPIO_PIN_5;                // CS High
    }
}
