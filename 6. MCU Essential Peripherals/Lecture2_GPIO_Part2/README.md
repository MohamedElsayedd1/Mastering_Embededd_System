# LCD and Keypad Drivers for ATmega32

This repository contains modular drivers for interfacing an LCD and a Keypad with the ATmega32 microcontroller. These drivers provide an easy-to-use API to integrate LCDs and Keypads into embedded applications.

- 8-bit LCD :
  
![8BIT_lcd_interface.gif](https://github.com/MohamedElsayedd1/Mastering_Embededd_System/blob/main/6.%20MCU%20Essential%20Peripherals/Lecture2_GPIO_Part2/8bit_lcd.gif)

- 4-bit LCD :

![4BIT_lcd_interface.gif](https://github.com/MohamedElsayedd1/Mastering_Embededd_System/blob/main/6.%20MCU%20Essential%20Peripherals/Lecture2_GPIO_Part2/4bit_lcd.gif)

- LCD and Keypad Interface :

![keypad_lcd_interface.gif](https://github.com/MohamedElsayedd1/Mastering_Embededd_System/blob/main/6.%20MCU%20Essential%20Peripherals/Lecture2_GPIO_Part2/keypad_lcd_interface.gif)

---

## Features

### LCD Driver
- Supports **8-bit** and **4-bit** modes.
- Provides functions for:
  - Initializing the LCD.
  - Sending commands and character data.
  - Setting cursor positions.
  - Displaying strings and numbers.
  - Creating and displaying custom characters.
- Compatible with **HD44780**-based LCDs.

### Keypad Driver
- Supports **4x4 matrix keypads**.
- Provides:
  - Initialization of keypad rows and columns.
  - Detection of key presses.
  - Returning the corresponding key value.

---

## Hardware Requirements

### LCD
- **Data Pins**: Connected to a port of the ATmega32 (e.g., PORTA).
- **Control Pins**: RS and EN connected to another port (e.g., PORTB).
- **Power**: 5V and GND.

### Keypad
- **Rows and Columns**: Connected to a single or multiple ports (e.g., PORTC).
- **Power**: 5V and GND.

---

## Software Configuration

### LCD Driver Configuration

Modify the following macros in `lcd.h` to configure the driver for your hardware setup:

- **Mode Selection**:
  ```c
  #define LCD_MODE LCD_8BIT_MODE // or LCD_4BIT_MODE
  ```

- **Pin and Port Definitions**:
  ```c
  #define LCD_DATA_PORT    PORTA
  #define LCD_CRTL_PORT    PORTB
  ```

### Keypad Driver Configuration

Define the pin configurations in the `keypad_t` structure:

```c
keypad_t keypad = {
    .keypad_rows = {{PORTC, 0}, {PORTC, 1}, {PORTC, 2}, {PORTC, 3}},
    .keypad_columns = {{PORTC, 4}, {PORTC, 5}, {PORTC, 6}, {PORTC, 7}}
};
```

---

## APIs

### LCD Driver

| Function                            | Description                                                  |
|-------------------------------------|--------------------------------------------------------------|
| `void lcd_initialize()`             | Initializes the LCD.                                         |
| `void lcd_send_command(uint8_t)`    | Sends a command to the LCD.                                  |
| `void lcd_send_char_data(uint8_t)`  | Sends a character to the LCD.                                |
| `void lcd_send_string(uint8_t[])`   | Displays a string on the LCD.                                |
| `void lcd_set_cursor_pos(row, col)` | Moves the cursor to a specified position (1-based index).    |
| `void lcd_send_custom_char(...)`    | Creates and displays a custom character.                    |

### Keypad Driver

| Function                      | Description                           |
|-------------------------------|---------------------------------------|
| `void keypad_initialize()`    | Configures rows as outputs and columns as inputs. |
| `uint8_t keypad_get_value()`  | Returns the value of the pressed key. |

---

## Example Usage

### LCD

```c
#include "lcd.h"

int main() {
    lcd_initialize();
    lcd_send_string((uint8_t *)"Hello, World!");
    while (1) {}
    return 0;
}
```

### Keypad

```c
#include "keypad.h"

int main() {
    keypad_t keypad = {
        .keypad_rows = {{PORTC, 0}, {PORTC, 1}, {PORTC, 2}, {PORTC, 3}},
        .keypad_columns = {{PORTC, 4}, {PORTC, 5}, {PORTC, 6}, {PORTC, 7}}
    };

    keypad_initialize(&keypad);

    while (1) {
        uint8_t key = keypad_get_value(&keypad);
        if (key) {
            // Do something with the key
        }
    }
    return 0;
}
```

---

## Notes
- Ensure pull-down resistors are connected to keypad column pins to avoid floating values.
- Adjust delays in the LCD driver for higher clock frequencies.
- Customize the keypad layout as per your hardware.

---

## License
This project is licensed under the MIT License. See the `LICENSE` file for details.

--- 

Feel free to modify this as needed for your project!


## Support
For any questions or support, please contact the repository maintainer.

