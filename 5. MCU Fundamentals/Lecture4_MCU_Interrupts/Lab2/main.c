/*
 * TriggerExternalInterrupt.c
 *
 * Created: 28/10/2024 8:16:31 PM
 * Author : Dubai Store
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdint.h>

#define PORTB	*((volatile uint8_t *)(0x38))
#define DDRB	*((volatile uint8_t *)(0x37))

#define PORTD	*((volatile uint8_t *)(0x32))
#define DDRD	*((volatile uint8_t *)(0x31))

#define GICR	*((volatile uint8_t *)(0x5B))
#define MCUCR	*((volatile uint8_t *)(0x55))
#define MCUCSR	*((volatile uint8_t *)(0x54))
#define GIFR	*((volatile uint8_t *)(0x5A))


void GPIO_Init(){
	// Configure PD1, PD2 and PB2 as input pins, pull-down resistors are off
	/* The DDxn bit in the DDRx Register selects the direction of this pin. If DDxn is written logic one, Pxn is configured
			as an output pin. If DDxn is written logic zero, Pxn is configured as an input pin */
	DDRB &= ~(1 << 2);
	DDRD &= ~(1 << 1);
	DDRD &= ~(1 << 2);
	
	// Configure PD4, PD5 and PD6 as output pins, off
	DDRD |= (1 << 4);
	DDRD |= (1 << 5);
	DDRD |= (1 << 6);
	PORTD &= ~((1 << 4) | (1 << 5) | (1 << 6)); // Ensure all LEDs are off
}

void EXTI_Init(){
	// Enable Global Interrupt
	sei(); // Set the Global Interrupt Enable bit
	// Enable Global Interrupt Requests For INT0, INT1, INT2
	GICR |= (0b111 << 5);
	// Set Interrupt Sense Control  for INT0
	MCUCR |= (0b11 << 0); // The rising edge of INT0 generates an interrupt request
	// Set Interrupt Sense Control  for INT1
	MCUCR |= (0b01 << 2); // Any logical change on INT1 generates an interrupt request
	// Set Interrupt Sense Control  for INT2
	MCUCSR  &= ~(1 << 6); // If ISC2 is written to zero, a falling edge on INT2 activates the interrupt
}

int main(void)
{
	GPIO_Init();
	EXTI_Init();
    /* Replace with your application code */
    while (1) 
    {
    }
}

ISR(INT0_vect){
	// INT0 Interrupt Flag is cleared automatically
	// Toggle PD4 bit
	PORTD |= (1 << 4);
	_delay_ms(1000);
	PORTD &= ~(1 << 4);
}

ISR(INT1_vect){
	// INT1 Interrupt Flag is cleared automatically
	// Toggle PD5 bit
	PORTD |= (1 << 5);
	_delay_ms(1000);
	PORTD &= ~(1 << 5);
}

ISR(INT2_vect){
	// INT2 Interrupt Flag is cleared automatically
	// Toggle PD6 bit
	PORTD |= (1 << 6);
	_delay_ms(1000);
	PORTD &= ~(1 << 6);
}