/*
 * main.c
 *
 * Created: 18/12/2024 1:31:39 AM
 *  Author: Dubai Store
 */ 

#include <xc.h>
#include <avr/io.h>
#include <util/delay.h>

#define F_MCU				1000000UL  // Frequency of internal MCU Oscillator

#define SPI_MOSI			PB5
#define SPI_MISO			PB6
#define SPI_CLK             PB7
#define SPI_SS				PB4


void SPI_MasterInit(){
	// Set MOSI, SS, CLK as output
	DDRB |= (1 << SPI_MOSI) | (1 << SPI_SS) | (1 << SPI_CLK);
	// Set the MCU as SPI Master mode
	SPCR |= (1 << MSTR);
	// Set the clock rate
	SPCR |= (1 << SPR0); // Fosc/16
	// Enable SPI Peripheral
	SPCR |= (1 << SPE);
}

uint8_t SPI_MasterTransmitRecieve(uint8_t data){
	// Write on SPDR
	SPDR = (uint8_t)data;
	// Wait for transmission to complete (SPIF flag is set)
	while(!((SPSR >> SPIF) & 0x1));
	return SPDR;
}

int main(void)
{
	// Initialize GPIOA as output for 7-segment display
	DDRA = 0xFF;
	// Initialize SPI Master Device
	SPI_MasterInit();
    while(1)
    {
		for(int i = 0; i <= 0xFF; i++){
			_delay_ms(250);
			uint8_t RecievedData = SPI_MasterTransmitRecieve(i); // Transmit & Recieve
			PORTA = RecievedData; // Display Recieved data on 7segment 
		}
    }
}