#include "./KEYPAD/keypad.h"
#include "./LCD/lcd.h"


// Define the CPU clock frequency
#ifndef F_CPU
#define F_CPU 1000000UL // 1 MHz
#endif

keypad_t kpad1 = {
    .keypad_rows = {
        {PORTC_, pin0},  // Row 0: Port C, Pin 0
        {PORTC_, pin1},  // Row 1: Port C, Pin 1
        {PORTC_, pin2},  // Row 2: Port C, Pin 2
        {PORTC_, pin3}   // Row 3: Port C, Pin 3
    },
    .keypad_columns = {
        {PORTC_, pin4},  // Column 0: Port C, Pin 4
        {PORTC_, pin5},  // Column 1: Port C, Pin 5
        {PORTC_, pin6},  // Column 2: Port C, Pin 6
        {PORTC_, pin7}   // Column 3: Port C, Pin 7
    }
};

void keypad_lcd_API(void);

int main() {
    keypad_initialize(&kpad1);
    lcd_initialize();

    char prev_key = '\0';  // Variable to store the previous key state

    while (1) {
        uint8_t current_key = keypad_get_value(&kpad1);  // Read the current key
        if (current_key != '\0' && current_key != prev_key) { 
            // If a valid key is pressed and it's different from the previous key
            lcd_send_char_data(current_key);  // Display the key on the LCD
            prev_key = current_key;          // Update the previous key state
            _delay_ms(200);                  // Debounce delay
        } else if (current_key == '\0') {
            // Reset the previous key state when no key is pressed
            prev_key = '\0';
        }
    }
    return 0;
}
