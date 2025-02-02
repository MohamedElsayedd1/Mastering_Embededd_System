/*
 * atmega32_SPI_driver.c
 *
 * Created: 21/12/2024 7:38:20 AM
 *  Author: Mohamed Elsayed
 */ 

#include "atmega32_SPI_driver.h"

// SPI initialization function (Master Mode)
void SPI_init(void){
	
	// MOSI :  PB5
	// SCK  :  PB7
	// MISO :  PB6
	// SS :    PB4
	
	#ifdef SPI_MASTER_MODE
	// Set MOSI ,SS and SCK output, MISO others input
	GPIO_InitPin(GPIO_PORT_B, MOSI, GPIO_PIN_OUTPUT);
	GPIO_InitPin(GPIO_PORT_B, SCK, GPIO_PIN_OUTPUT);
	GPIO_InitPin(GPIO_PORT_B, SS, GPIO_PIN_OUTPUT);
	GPIO_InitPin(GPIO_PORT_B, MISO, GPIO_PIN_INPUT);
	// Set Master Mode
	SET_BIT(SPCR, MSTR);
	// Set Clock Rate Fclk/16
	SET_BIT(SPCR, SPR0);
	#endif
	
	#ifdef SPI_SLAVE_MODE
	// Set MISO output, all others input
	GPIO_InitPin(GPIO_PORT_B, MOSI, GPIO_PIN_INPUT);
	GPIO_InitPin(GPIO_PORT_B, SCK, GPIO_PIN_INPUT);
	GPIO_InitPin(GPIO_PORT_B, SS, GPIO_PIN_INPUT);
	GPIO_InitPin(GPIO_PORT_B, MISO, GPIO_PIN_OUTPUT);
	// Set Slave Mode
	RESET_BIT(SPCR, MSTR);
	#endif
	
	// Enable SPI
	SET_BIT(SPCR, SPE);
}

// SPI transmit function
void SPI_transmit(uint8_t data){
	/* Start transmission */
	SPDR = data;
	/* Wait for transmission complete */
	while(!(READ_BIT(SPSR, SPIF)));
}

// SPI receive function
uint8_t SPI_receive(void){
	/* Wait for reception complete */
	while(!(READ_BIT(SPSR, SPIF)));
	
	/* Return data register */
	return SPDR;
}

// SPI transmit and receive function (simultaneously)
uint8_t SPI_transmitReceive(uint8_t data) {
	SPDR = data;  // Load data into the SPI data register for transmission

	// Wait until both transmission and reception are complete
	while(!(READ_BIT(SPSR, SPIF)));

	return SPDR;
}