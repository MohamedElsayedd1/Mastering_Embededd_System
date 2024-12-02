# STM32 Drivers for External LCD, Keypad, and 7-Segment Display

## Overview
This repository provides drivers and sample code to interface an LCD, Keypad, and 7-Segment Display with an STM32 microcontroller using STM32CubeIDE. It demonstrates how to initialize and use these peripherals to display characters, numbers, and interact with user input through a keypad.

![lcd_keypad.gif](https://github.com/MohamedElsayedd1/Mastering_Embededd_System/blob/main/6.%20MCU%20Essential%20Peripherals/Lecture3_GPIO_Part3/2.%20Section/stm32f103x6_Drivers/Lcd_Keypad.gif)

## Features
- **LCD Driver**: Supports character display with position and command functionalities.
- **Keypad Driver**: Enables reading user input from a 4x4 matrix keypad.
- **7-Segment Driver**: Displays numbers on a 7-segment display using GPIO pins.
- Fully configurable GPIO and timing using STM32 HAL.

---

## Hardware Requirements
- STM32 microcontroller
- External LCD (HD44780 compatible)
- 4x4 Keypad
- 7-Segment Display
- GPIO pins for peripheral connections

---

## Connections
### LCD
- Data Pins: GPIOA[0:7]
- Control Pins: GPIOA[8:9] (RS and EN)

### Keypad
- Row and Column Pins: GPIOB[0:8]

### 7-Segment
- Segments: GPIOB[9:15]

---

## Software Requirements
- **STM32CubeIDE**: For code development and debugging.
- **Proteus**: For simulation (optional).