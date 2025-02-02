
/*
 * atmega32_ADC_driver.h
 *
 * Created: 02/02/2025 4:41:31 PM
 *  Author: Mohamed Elsayed
 */ 

#include <avr/io.h>
#include <stdint.h>

// Enum for ADC channels
typedef enum {
	ADC_CHANNEL_0 = 0, // ADC0
	ADC_CHANNEL_1,     // ADC1
	ADC_CHANNEL_2,     // ADC2
	ADC_CHANNEL_3,     // ADC3
	ADC_CHANNEL_4,     // ADC4
	ADC_CHANNEL_5,     // ADC5
	ADC_CHANNEL_6,     // ADC6
	ADC_CHANNEL_7      // ADC7
} ADC_Channel_t;

// Function prototypes
void ADC_Init(void);
uint16_t ADC_Read(uint8_t channel);

