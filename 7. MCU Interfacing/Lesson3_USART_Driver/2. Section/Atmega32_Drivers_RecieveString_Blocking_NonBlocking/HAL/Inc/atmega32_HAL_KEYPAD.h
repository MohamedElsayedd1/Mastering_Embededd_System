/*
 * atmega32_HAL_KEYPAD.h
 *
 * Created: 05/12/2024 8:26:14 PM
 *  Author: Dubai Store
 */ 


#ifndef ATMEGA32_HAL_KEYPAD_H
#define ATMEGA32_HAL_KEYPAD_H

#include "atmega32_GPIO_driver.h"

// Define keypad rows and columns
#define KEYPAD_ROWS_PORT    GPIO_PORT_B
#define KEYPAD_COLS_PORT    GPIO_PORT_C

#define KEYPAD_ROW0_PIN     0
#define KEYPAD_ROW1_PIN     1
#define KEYPAD_ROW2_PIN     2
#define KEYPAD_ROW3_PIN     3

#define KEYPAD_COL0_PIN     0
#define KEYPAD_COL1_PIN     1
#define KEYPAD_COL2_PIN     2
#define KEYPAD_COL3_PIN     3

// Function prototypes
void KEYPAD_Init(void);
char KEYPAD_GetKey(void);

#endif // ATMEGA32_HAL_KEYPAD_H
