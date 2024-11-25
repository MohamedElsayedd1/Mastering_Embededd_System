#ifndef _MEMMAP_H_
#define _MEMMAP_H_

#include <stdint.h>
#include <util/delay.h>

#define PORTA   *((volatile uint8_t *)0x3B)
#define DDRA    *((volatile uint8_t *)0x3A)
#define PINA    *((volatile uint8_t *)0x39)

#define PORTB   *((volatile uint8_t *)0x38)
#define DDRB    *((volatile uint8_t *)0x37)
#define PINB    *((volatile uint8_t *)0x36)

#define PORTC   *((volatile uint8_t *)0x35)
#define DDRC    *((volatile uint8_t *)0x34)
#define PINC    *((volatile uint8_t *)0x33)

#define PORTD   *((volatile uint8_t *)0x32)
#define DDRD    *((volatile uint8_t *)0x31)
#define PIND    *((volatile uint8_t *)0x30)

#define PA0     0
#define PA1     1
#define PA2     2
#define PA3     3
#define PA4     4
#define PA5     5
#define PA6     6
#define PA7     7
#define PA8     8

#define PB0     0
#define PB1     1
#define PB2     2
#define PB3     3
#define PB4     4
#define PB5     5
#define PB6     6
#define PB7     7
#define PB8     8

#define PC0     0
#define PC1     1
#define PC2     2
#define PC3     3
#define PC4     4
#define PC5     5
#define PC6     6
#define PC7     7
#define PC8     8

#define PD0     0
#define PD1     1
#define PD2     2
#define PD3     3
#define PD4     4
#define PD5     5
#define PD6     6
#define PD7     7
#define PD8     8

// Set a specific bit (set to 1)
#define SET_BIT(REG, BIT_POS)   (REG |= (1 << BIT_POS))

// Clear a specific bit (set to 0)
#define CLEAR_BIT(REG, BIT_POS) (REG &= ~(1 << BIT_POS))

// Toggle a specific bit (flip between 0 and 1)
#define TOGGLE_BIT(REG, BIT_POS) (REG ^= (1 << BIT_POS))

// Read a specific bit (returns 1 if bit is set, 0 if bit is cleared)
#define READ_BIT(REG, BIT_POS)   ((REG >> BIT_POS) & 0x01)


typedef enum
{
    PORTA_ = 0,
    PORTB_,
    PORTC_,
    PORTD_
} port_t;

typedef enum
{
    pin0 = 0,
    pin1,
    pin2,
    pin3,
    pin4,
    pin5,
    pin6,
    pin7,
    pin8
} pin_t;

typedef struct{
    port_t port;
    pin_t pin;
}pin_config_t;

#endif