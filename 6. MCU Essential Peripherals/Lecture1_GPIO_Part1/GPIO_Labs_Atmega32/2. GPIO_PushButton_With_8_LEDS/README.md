# Embedded System Project - AVR ATmega32 Button-Controlled LED Toggle

This project uses an ATmega32 microcontroller to toggle LEDs on Port A based on the state of an external button connected to Port C. When the button connected to `PC0` is pressed, it toggles each LED on Port A sequentially.

## Simulation Video
![Watch the simulation video](https://github.com/MohamedElsayedd1/Mastering_Embededd_System/blob/main/6.%20MCU%20Essential%20Peripherals/Lecture1_GPIO_Part1/GPIO_Labs_Atmega32/2.%20GPIO_PushButton_With_8_LEDS/GPIO_Lab1.gif)

## Project Structure

- **main.c**: Contains the main application logic for initializing GPIO, reading button input, and toggling LEDs.
- **MemMap.h**: Defines the memory mappings for ATmega32 microcontroller registers and includes helpful macros for bit manipulation.
- **Makefile**: Automates the build and cleanup processes for the project.

## Requirements

- **Toolchain**: `avr-gcc` for compiling and linking the code.
- **Microcontroller**: ATmega32.
- **Make**: GNU Make is used to automate the build process.

## File Descriptions

- **Makefile**: Configures the AVR build process. Key variables include:
  - `CC`: Specifies `avr-gcc` as the compiler.
  - `CFLAGS`: Compiler flags with MCU type, CPU frequency, and optimization/debug settings.
  - `SRC`: The source file location.
  - `OBJ`: The object file generated from the source file.
  - `TARGET_ELF` and `TARGET_HEX`: The compiled binary files for programming the microcontroller.

## Setup and Build Instructions

1. Clone the repository:
   ```bash
   git clone https://github.com/MohamedElsayedd1/Mastering_Embedded_System.git
   ```
2. Navigate to the project directory:
   ```bash
   cd Mastering_Embedded_System
   ```
3. Compile and build the project:
   ```bash
   make
   ```
   - This command compiles `main.c`, generates an ELF file, and converts it to a HEX file for microcontroller programming.

4. Clean up generated files:
   ```bash
   make clean
   ```

## Code Explanation

### main.c

The code initializes GPIO and sets up button-controlled LED toggling on Port A.

- **GPIO_Init()**: Sets Port A as output for the LEDs and configures `PC0` as an input with a tri-state configuration.
- **myDelay(uint32_t delay)**: Simple delay function to control toggle speed if needed.
- **main()**:
  - Continuously monitors `PC0` for a button press.
  - On a rising edge of the button signal (button press), it toggles the next LED on Port A.
  - Cycles through LEDs from `PA0` to `PA7`, resetting to `PA0` after `PA7`.

### MemMap.h

Defines register addresses and bit manipulation macros, enabling easy GPIO control.

- `PORTA`, `DDRA`, `PORTC`, `DDRC`, and `PINC`: Direct register mappings for Port A and Port C.
- Bitwise macros `SET_BIT`, `RESET_BIT`, `TOGGLE_BIT`, and `READ_BIT` for efficient bit-level operations.

### Button-Controlled LED Toggle

The button's state on `PC0` is monitored, with logic to detect button presses:

- `PC0_Btn_Prevstate`: Holds the previous state of the button to detect changes.
- `ledCounter`: Tracks the current LED to toggle on Port A.

In the `main()` loop:
- When `PC0` is pressed, the next LED in sequence toggles.
- `ledCounter` resets to 0 after reaching 8 (i.e., toggling all LEDs).

## Makefile Commands

- **Build the project**: `make`
- **Clean up files**: `make clean`

This project demonstrates using an input button to control sequential LED toggling, a fundamental embedded systems concept.
