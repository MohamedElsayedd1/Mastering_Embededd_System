/*
 * keypad.c
 *
 *  Created on: Nov 29, 2024
 *      Author: Mohamed Elsayed
 */

#include "keypad.h"

int Key_padRow[] = {R0, R1, R2, R3}; // Rows
int Key_padCol[] = {C0, C1, C2, C3}; // Columns

const char KEYPAD_MAP[4][4] = {
    {'7', '8', '9', '/'},
    {'4', '5', '6', '*'},
    {'1', '2', '3', '-'},
    {'?', '0', '=', '+'}
};

void delay_ms(uint32 time) {
    volatile uint32 i, j;
    for (i = 0; i < time; i++)
        for (j = 0; j < 255; j++);
}

void Keypad_init() {
    GPIO_PinConfig_t PinCfg;

    // Initialize rows as output
    for (int i = 0; i < 4; i++) {
        PinCfg.PinNum = Key_padRow[i];
        PinCfg.PinMode = GPIO_OUTPUT_10MHZ;
        PinCfg.PinCNF = GPIO_CNF_PUSH_PULL_OUTPUT;
        MCAL_GPIO_Init(KEYPAD_PORT, &PinCfg);
        MCAL_GPIO_WritePin(KEYPAD_PORT, Key_padRow[i], GPIO_LOW); // Default to LOW
    }

    // Initialize columns as input with pull-up
    for (int i = 0; i < 4; i++) {
        PinCfg.PinNum = Key_padCol[i];
        PinCfg.PinMode = GPIO_INPUT;
        PinCfg.PinCNF = GPIO_CNF_PULL_UP_DOWN_INPUT;
        PinCfg.PinState = GPIO_HIGH;
        MCAL_GPIO_Init(KEYPAD_PORT, &PinCfg);
    }
}

char lookupKey(int row, int col) {
    return KEYPAD_MAP[row][col];
}

char Keypad_getkey() {
    for (int col = 0; col < 4; col++) {
        // Set all columns to HIGH (input pull-up ensures this naturally)
        MCAL_GPIO_WritePin(KEYPAD_PORT, Key_padCol[col], GPIO_LOW); // Set active column to LOW

        for (int row = 0; row < 4; row++) {
            if (MCAL_GPIO_ReadPin(KEYPAD_PORT, Key_padRow[row]) == GPIO_LOW) { // Detect key press
                delay_ms(20); // Debounce delay
                while (MCAL_GPIO_ReadPin(KEYPAD_PORT, Key_padRow[row]) == GPIO_LOW); // Wait for release
                MCAL_GPIO_WritePin(KEYPAD_PORT, Key_padCol[col], GPIO_HIGH); // Reset column
                return lookupKey(row, col);
            }
        }

        MCAL_GPIO_WritePin(KEYPAD_PORT, Key_padCol[col], GPIO_HIGH); // Reset column
    }

    return '\0'; // No key pressed
}

