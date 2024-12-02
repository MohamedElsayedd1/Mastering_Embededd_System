# Embedded System Project - AVR ATmega32 GPIO Control

This project demonstrates a simple GPIO control program on an AVR ATmega32 microcontroller. The program sets up the GPIO pins on Port A as outputs and then sequentially sets and resets them with a delay.

## Simulation Video
![Watch the simulation video](https://github.com/MohamedElsayedd1/Mastering_Embededd_System/blob/main/6.%20MCU%20Essential%20Peripherals/Lecture1_GPIO_Part1/GPIO_Labs_Atmega32/1.%20GPIO_Switch_8_LEDS/GPIO_Lab.gif)

## Project Structure

- **main.c**: Contains the main application logic for GPIO control on Port A.
- **MemMap.h**: Defines memory mappings for the ATmega32 microcontroller registers used in the program.
- **Makefile**: Automates the compilation, linking, and cleanup process.
  
## Requirements

- **Toolchain**: `avr-gcc` for compiling and linking the code.
- **Microcontroller**: ATmega32.
- **Make**: GNU Make is used to process the `Makefile` commands.

## File Descriptions

- **Makefile**: Configures the build process. Key components:
  - `CC`: Compiler set to `avr-gcc`.
  - `CFLAGS`: Compiler flags, including optimization, debugging, and MCU specifications.
  - `SRC`: Source directory path and main source file.
  - `OBJ`: Object file created from the source file.
  - `TARGET_ELF`: The compiled ELF binary file.
  - `TARGET_HEX`: The output HEX file used for microcontroller programming.
  
## Setup and Build Instructions

1. Clone this repository:
   ```bash
   git clone https://github.com/MohamedElsayedd1/Mastering_Embedded_System.git
   ```
2. Navigate to the project directory:
   ```bash
   cd Mastering_Embedded_System
   ```
3. Compile and generate the program files:
   ```bash
   make
   ```
   - This command compiles `main.c`, links it to create `program.elf`, and then converts it to `program.hex` for programming the microcontroller.

4. To clean up generated files, run:
   ```bash
   make clean
   ```

## Code Explanation

### main.c

The `main.c` file initializes Port A as output and controls each pin with a delay.

- **GPIO_Init()**: Sets all pins on Port A as outputs.
- **myDelay(uint32_t delay)**: Simple delay function.
- **main()**: Toggles each bit on Port A sequentially with a delay, creating a pattern of LED lighting.

### MemMap.h

Defines register addresses and bit manipulation macros for better readability and direct hardware access.

- `PORTA`, `DDRA`, `PINA`: Direct register addresses for Port A.
- Bitwise macros like `SET_BIT`, `RESET_BIT`, `TOGGLE_BIT`, and `READ_BIT` provide easy control over individual bits.

## Makefile Usage

- **Build the project**: `make`
- **Clean up files**: `make clean`
