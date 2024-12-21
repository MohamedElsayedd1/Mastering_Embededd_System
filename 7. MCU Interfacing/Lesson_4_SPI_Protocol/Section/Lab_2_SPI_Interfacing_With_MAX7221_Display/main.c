/*
 * main.c
 *
 * Created: 18/12/2024 1:31:39 AM
 *  Author: Mohamed Elsayed
 */ 

#define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>

#define SS 4
#define MOSI 5
#define SCK 7


#include <avr/io.h>
#include <util/delay.h>

#define SPI_SS   PB4
#define SPI_MOSI PB5
#define SPI_SCK  PB7

void SPI_MasterInit() {
	DDRB |= (1 << SPI_MOSI) | (1 << SPI_SCK) | (1 << SPI_SS);  // Set MOSI, SCK, SS as output
	SPCR = (1 << SPE) | (1 << MSTR) | (0 << CPOL) | (0 << CPHA) | (1 << SPR0);  // SPI mode 0, Fosc/16
}

void SPI_MasterTransmit(uint8_t data) {
	SPDR = data;
	while (!(SPSR & (1 << SPIF)));  // Wait for transmission to complete
}

void MAX7219_Write(uint8_t address, uint8_t data) {
	PORTB &= ~(1 << SPI_SS);  // Pull CS low
	SPI_MasterTransmit(address);  // Send address (digit register)
	SPI_MasterTransmit(data);  // Send data (digit value)
	PORTB |= (1 << SPI_SS);  // Pull CS high
}

void MAX7219_Init() {
	MAX7219_Write(0x09, 0xFF);  // Exit shutdown mode
	MAX7219_Write(0x0A, 0xFF);  // Mid brightness
	MAX7219_Write(0x0B, 0xF7);  // Scan all 8 digits
	MAX7219_Write(0x0C, 0x01);  // Disable test mode
}

void TestAllSegments() {
	for (uint8_t i = 0; i < 8; i++) {
		MAX7219_Write(i + 1, 0x7F);  // All segments ON for each digit (0x7F is 1111111, all segments ON)
		_delay_ms(500);  // Wait for 500ms
		MAX7219_Write(i + 1, 0x00);  // All segments OFF for each digit
		_delay_ms(500);  // Wait for 500ms
	}
}

void DisplayDigit(uint8_t digit, uint8_t value) {
	MAX7219_Write(digit, value);  // Write the value to the specified digit
}

int main(void) {
	SPI_MasterInit();  // Initialize SPI
	MAX7219_Init();    // Initialize MAX7219

	while (1) {
		// Display digits 1 to 8 on each of the 8 digits of the MAX7219
		DisplayDigit(1, 0x01); 
		DisplayDigit(2, 0x02); 
		DisplayDigit(3, 0x03);  
		DisplayDigit(4, 0x04);  
		DisplayDigit(5, 0x05);  
		DisplayDigit(6, 0x06);  
		DisplayDigit(7, 0x07);  
		DisplayDigit(8, 0x08); 
		_delay_ms(1000);  // Wait for 1 second

		TestAllSegments();
	}
}
