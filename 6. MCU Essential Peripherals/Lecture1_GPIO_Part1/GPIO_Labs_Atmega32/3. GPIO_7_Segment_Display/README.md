# 7-Segment Display Counter using ATmega32

## Overview

This project demonstrates a basic 7-segment display counter using the ATmega32 microcontroller. The code controls two 7-segment displays to count from `00` to `99`. It uses GPIO for display control and simple delay loops to manage timing.

![GPIO_LAB3](https://github.com/MohamedElsayedd1/Mastering_Embededd_System/blob/main/6.%20MCU%20Essential%20Peripherals/Lecture1_GPIO_Part1/GPIO_Labs_Atmega32/3.%20GPIO_7_Segment_Display/GPIO_Lab3.gif)

---

## Features

- **Dual 7-Segment Display Control**:
  - Displays numbers from `00` to `99`.
  - Each digit is updated sequentially.
- **Custom Bit Manipulation Macros**:
  - Simplifies GPIO operations (e.g., `SET_BIT`, `RESET_BIT`).
- **Delay Function**:
  - Uses a busy-wait loop for timing.

---

## Hardware Requirements

- **Microcontroller**: ATmega32
- **7-Segment Displays**: Two common cathode or common anode (with appropriate resistors).
- **Connections**:
  - **PORTA[0:3]**: Lower 4 bits for the units digit.
  - **PORTA[4:7]**: Higher 4 bits for the tens digit.
- **Clock Frequency**: 1 MHz (default internal clock of ATmega32).

---

## Software Configuration

### GPIO Configuration

The GPIO initialization sets the following:

- **PORTA**: Configured as output for the 7-segment display.

```c
void GPIO_Init(){
    DDRA = 0xFF; // Configure all pins on PORTA as output
}
```

### 7-Segment Mapping

The `_7Seg` array holds the binary representations of digits `0` to `9`:

```c
uint8_t _7Seg[] = {0b0000, 0b0001, 0b0010, 0b0011, 0b0100, 0b0101, 0b0110, 0b0111, 0b1000, 0b1001};
```

Each index corresponds to a digit.

---

## Code Explanation

### Main Function

1. **Initialization**:
   - Configure GPIO pins for the 7-segment display.
2. **Counter Logic**:
   - Use nested loops to iterate through tens (`i`) and units (`j`) digits.
   - Update the respective 4-bit segments of `PORTA`.
3. **Delay**:
   - Introduce a delay to control the display refresh rate.

---

## Code Walkthrough

```c
void main(){
    GPIO_Init(); // Initialize GPIO pins
    while(1){
        volatile uint8_t i = 0;
        volatile uint8_t j = 0;
        for (i = 0; i < 10; i++){ // Tens digit
            PORTA &= ~(0b1111 << 4);  // Clear higher 4 bits
            PORTA |= (_7Seg[i] << 4); // Set higher 4 bits for tens digit
            for (j = 0; j < 10; j++){ // Units digit
                PORTA &= ~(0b1111 << 0);  // Clear lower 4 bits
                PORTA |= (_7Seg[j] << 0); // Set lower 4 bits for units digit
                myDelay(5000); // Wait for a short period
            }
        }
    }
}
```

---

## APIs and Macros

### GPIO Macros

| Macro                      | Description                         |
|----------------------------|-------------------------------------|
| `SET_BIT(REG, BIT_POS)`    | Sets a specific bit in a register. |
| `RESET_BIT(REG, BIT_POS)`  | Clears a specific bit.             |
| `TOGGLE_BIT(REG, BIT_POS)` | Toggles a specific bit.            |
| `READ_BIT(REG, BIT_POS)`   | Reads the value of a bit.          |

### Delay Function

```c
void myDelay(uint32_t delay){
    while(delay--);
}
```

- Introduces a simple busy-wait loop for delays.
- The delay duration is proportional to the `delay` value and the clock frequency.

---

## Example Timing

| Delay Parameter | Approximate Time (1 MHz Clock) |
|-----------------|--------------------------------|
| `5000`          | 5 ms                          |
| `10000`         | 10 ms                         |

---

## Notes

- Ensure proper current-limiting resistors are used for the 7-segment displays.
- The delay is approximate and not precise; consider using a timer for accurate timing.
- Adjust `_7Seg` values for compatibility with specific 7-segment display types (common anode or cathode).

---

## License

This project is licensed under the MIT License. See the `LICENSE` file for details.

