#include "keypad.h"


uint8_t *PORT_REGISTERS[] = {&PORTA, &PORTB, &PORTC, &PORTD};
uint8_t *DDR_REGISTERS[] = {&DDRA, &DDRB, &DDRC, &DDRD};
uint8_t *PIN_REGISTERS[] = {&PINA, &PINB, &PINC, &PIND};

// Define the keypad layout
const char KEYPAD_VALUES[KEYPAD_ROWS][KEYPAD_COLUMNS] = {
    {'7', '8', '9', '/'},
    {'4', '5', '6', '*'},
    {'1', '2', '3', '-'},
    {'#', '0', '=', '+'}
};


void keypad_initialize(keypad_t *kpad){
    // Set ROWS as output
    for (int i = 0; i < KEYPAD_ROWS; i++){
        SET_BIT(*DDR_REGISTERS[kpad->keypad_rows[i].port], kpad->keypad_rows[i].pin);
    }
    
    // Set Columns as input
    for (int i = 0; i < KEYPAD_COLUMNS; i++){ 
        CLEAR_BIT(*DDR_REGISTERS[kpad->keypad_columns[i].port], kpad->keypad_columns[i].pin);
    }
}

uint8_t keypad_get_value(keypad_t *kpad) {
    // Iterate over each row
    for (int row = 0; row < KEYPAD_ROWS; row++) {
        // Set the current row HIGH and all others LOW
        for (int r = 0; r < KEYPAD_ROWS; r++) {
            if (r == row) {
                SET_BIT(*PORT_REGISTERS[kpad->keypad_rows[r].port], kpad->keypad_rows[r].pin);
            } else {
                CLEAR_BIT(*PORT_REGISTERS[kpad->keypad_rows[r].port], kpad->keypad_rows[r].pin);
            }
        }

        // Check each column for a pressed key
        for (int col = 0; col < KEYPAD_COLUMNS; col++) {
            if (READ_BIT(*PIN_REGISTERS[kpad->keypad_columns[col].port], kpad->keypad_columns[col].pin) == 1) {
                // Return the corresponding key value
                return KEYPAD_VALUES[row][col];
            }
        }
    }

    // Return 0 if no key is pressed
    return 0;
}