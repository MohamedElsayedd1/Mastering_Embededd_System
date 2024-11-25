#ifndef _KEYPAD_H_
#define _KEYPAD_H_

#include "../MemMap.h"

#define KEYPAD_ROWS                 4
#define KEYPAD_COLUMNS              4

#define KEYPAD_ROWS_PORT            PORTC
#define KEYPAD_COLUMNS_PORT         PORTC

#define R0                          0
#define R1                          1
#define R2                          2
#define R3                          3
#define C0                          0
#define C1                          1
#define C2                          2
#define C3                          3

typedef struct{
    pin_config_t keypad_rows[KEYPAD_ROWS];
    pin_config_t keypad_columns[KEYPAD_COLUMNS];
}keypad_t;

void keypad_initialize(keypad_t *kpad);
uint8_t keypad_get_value(keypad_t *kpad);

#endif