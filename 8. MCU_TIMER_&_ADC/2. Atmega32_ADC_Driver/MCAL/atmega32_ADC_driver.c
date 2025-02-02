
/*
 * atmega32_ADC_driver.c
 *
 * Created: 02/02/2025 4:41:51 PM
 *  Author: Mohamed Elsayed 
 */ 

#include "atmega32_ADC_driver.h"

// Initialize the ADC
void ADC_Init(void) {
	// Set reference voltage to AVCC (5V) and select ADC0 as default channel
	ADMUX = (1 << REFS0);
	
	// Enable ADC and set prescaler to 128 (16MHz/128 = 125kHz)
	ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}

// Read ADC value from a specific channel
uint16_t ADC_Read(uint8_t channel) {
	// Select the channel (0-7) and keep the reference voltage bits unchanged
	ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);
	
	// Start the conversion
	ADCSRA |= (1 << ADSC);
	
	// Wait for the conversion to complete
	while (ADCSRA & (1 << ADSC));
	
	// Read the ADC value (10-bit)
	return ADC;
}