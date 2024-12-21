/*
 * main.c
 *
 * Created: 18/12/2024 2:12:01 AM
 *  Author: Dubai Store
 */ 

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


void SPI_SlaveInit(){
	// Set MISO as output; MOSI, SCK, SS as input
	DDRB |= (1 << SPI_MISO);
	DDRB &= ~((1 << SPI_MOSI) | (1 << SPI_CLK) | (1 << SPI_SS));
	// Enable SPI Peripheral
	SPCR |= (1 << SPE);
}

uint8_t SPI_SlaveTransmitRecieve(uint8_t data){
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
	SPI_SlaveInit();
    while(1)
    {
		for(int i = 0xFF; i >= 0; i--){
			_delay_ms(250);
			uint8_t RecievedData = SPI_SlaveTransmitRecieve(i); // Transmit & Recieve
			PORTA = RecievedData; // Display Recieved data on 7segment 
		}
    }
}