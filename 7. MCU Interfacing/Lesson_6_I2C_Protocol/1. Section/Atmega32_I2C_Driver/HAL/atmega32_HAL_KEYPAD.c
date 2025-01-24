/*
 * CFile1.c
 *
 * Created: 05/12/2024 8:26:37 PM
 *  Author: Dubai Store
 */ 

#include "atmega32_HAL_KEYPAD.h"
#include <util/delay.h>

// Define the keypad key mapping
static const char KEYPAD_KEYS[4][4] = {
	{'1', '2', '3', 'A'},
	{'4', '5', '6', 'B'},
	{'7', '8', '9', 'C'},
	{'*', '0', '#', 'D'}
};

void KEYPAD_Init(void) {
	// Configure rows as output
	GPIO_InitPin(KEYPAD_ROWS_PORT, KEYPAD_ROW0_PIN, GPIO_PIN_OUTPUT);
	GPIO_InitPin(KEYPAD_ROWS_PORT, KEYPAD_ROW1_PIN, GPIO_PIN_OUTPUT);
	GPIO_InitPin(KEYPAD_ROWS_PORT, KEYPAD_ROW2_PIN, GPIO_PIN_OUTPUT);
	GPIO_InitPin(KEYPAD_ROWS_PORT, KEYPAD_ROW3_PIN, GPIO_PIN_OUTPUT);

	// Configure columns as input with pull-up
	GPIO_InitPin(KEYPAD_COLS_PORT, KEYPAD_COL0_PIN, GPIO_PIN_INPUT);
	GPIO_WritePin(KEYPAD_COLS_PORT, KEYPAD_COL0_PIN, GPIO_PIN_HIGH); // Enable pull-up
	GPIO_InitPin(KEYPAD_COLS_PORT, KEYPAD_COL1_PIN, GPIO_PIN_INPUT);
	GPIO_WritePin(KEYPAD_COLS_PORT, KEYPAD_COL1_PIN, GPIO_PIN_HIGH);
	GPIO_InitPin(KEYPAD_COLS_PORT, KEYPAD_COL2_PIN, GPIO_PIN_INPUT);
	GPIO_WritePin(KEYPAD_COLS_PORT, KEYPAD_COL2_PIN, GPIO_PIN_HIGH);
	GPIO_InitPin(KEYPAD_COLS_PORT, KEYPAD_COL3_PIN, GPIO_PIN_INPUT);
	GPIO_WritePin(KEYPAD_COLS_PORT, KEYPAD_COL3_PIN, GPIO_PIN_HIGH);
}

char KEYPAD_GetKey(void) {
	// Iterate through rows
	for (uint8_t row = 0; row < 4; row++) {
		// Set the current row to LOW and others to HIGH
		GPIO_WritePin(KEYPAD_ROWS_PORT, KEYPAD_ROW0_PIN, row == 0 ? GPIO_PIN_LOW : GPIO_PIN_HIGH);
		GPIO_WritePin(KEYPAD_ROWS_PORT, KEYPAD_ROW1_PIN, row == 1 ? GPIO_PIN_LOW : GPIO_PIN_HIGH);
		GPIO_WritePin(KEYPAD_ROWS_PORT, KEYPAD_ROW2_PIN, row == 2 ? GPIO_PIN_LOW : GPIO_PIN_HIGH);
		GPIO_WritePin(KEYPAD_ROWS_PORT, KEYPAD_ROW3_PIN, row == 3 ? GPIO_PIN_LOW : GPIO_PIN_HIGH);

		// Small delay to stabilize the signal
		_delay_us(5);

		// Check columns for a LOW signal
		for (uint8_t col = 0; col < 4; col++) {
			if (GPIO_ReadPin(KEYPAD_COLS_PORT, KEYPAD_COL0_PIN + col) == GPIO_PIN_LOW) {
				// Wait for key debounce
				_delay_ms(20);

				// Check again to confirm the key press
				if (GPIO_ReadPin(KEYPAD_COLS_PORT, KEYPAD_COL0_PIN + col) == GPIO_PIN_LOW) {
					return KEYPAD_KEYS[row][col];
				}
			}
		}
	}

	return '\0'; // No key pressed
}