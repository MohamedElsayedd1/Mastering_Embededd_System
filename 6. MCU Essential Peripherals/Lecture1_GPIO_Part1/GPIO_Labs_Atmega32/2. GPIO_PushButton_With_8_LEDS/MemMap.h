#ifndef _MEMMAP_H_
#define _MEMMAP_H_

#include <stdint.h>

#define PORTA   *((volatile uint8_t *)0x3B)
#define DDRA    *((volatile uint8_t *)0x3A)
#define PINA    *((volatile uint8_t *)0x39)

#endif