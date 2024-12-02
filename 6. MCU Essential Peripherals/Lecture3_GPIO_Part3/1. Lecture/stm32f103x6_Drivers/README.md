
# STM32F103x6 GPIO Driver

This repository contains a custom GPIO driver for the STM32F103x6 microcontroller. The driver provides APIs for configuring, reading, writing, toggling, and locking GPIO pins.

![gpio_test_driver.gif](https://github.com/MohamedElsayedd1/Mastering_Embededd_System/blob/main/6.%20MCU%20Essential%20Peripherals/Lecture3_GPIO_Part3/1.%20Lecture/stm32f103x6_Drivers/gpio_test_driver.gif)

## Features

- Pin initialization with configurable modes and states.
- Support for input, output, and alternate function modes.
- Functions for reading/writing to GPIO pins and ports.
- Pin toggling for output pins.
- GPIO pin locking mechanism for enhanced safety.
- Compatible with STM32F103x6 microcontrollers.

## Getting Started

### Prerequisites

- STM32CubeIDE or any ARM-based development environment.
- STM32F103x6 microcontroller or simulator (e.g., Proteus).

### Files

1. **`stm32f103x6_GPIO_driver.h`**: Contains type definitions, macros, and function prototypes.
2. **`stm32f103x6_GPIO_driver.c`**: Implements the GPIO driver functions.

### Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/your-repo/gpio-driver.git
   ```
2. Include `stm32f103x6_GPIO_driver.h` and `stm32f103x6_GPIO_driver.c` in your project.
3. Use the provided APIs to manage GPIO pins.

## Usage

### Example: Initialize a GPIO Pin

```c
GPIO_PinConfig_t pinConfig;
pinConfig.PinNum = GPIO_PIN5;
pinConfig.PinMode = GPIO_OUTPUT_2MHZ;
pinConfig.PinState = GPIO_LOW;
pinConfig.PinCNF = GPIO_CNF_PUSH_PULL_OUTPUT;

MCAL_GPIO_Init(GPIOA, &pinConfig);
```

### Example: Write to a GPIO Pin

```c
MCAL_GPIO_WritePin(GPIOA, GPIO_PIN5, GPIO_HIGH);
```

### Example: Toggle a GPIO Pin

```c
MCAL_GPIO_TogglePin(GPIOA, GPIO_PIN5);
```

### Example: Read a GPIO Pin

```c
uint8_t state = MCAL_GPIO_ReadPin(GPIOA, GPIO_PIN5);
```
