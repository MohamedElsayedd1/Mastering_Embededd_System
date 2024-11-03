# STM32 Button LED Simulation

This project demonstrates toggling LEDs using push buttons on an STM32 microcontroller in Proteus.

## Code
The main code for this project is in `main.c`, which handles button presses on `PA1` and `PA13` to toggle LEDs on `PB1` and `PB13`.

## Proteus Simulation Setup

1. Open Proteus and create a new project.
2. Add an STM32F103C8 microcontroller.
3. Connect `PA1` and `PA13` to push buttons.
4. Connect `PB1` and `PB13` to LEDs.
5. Load the compiled `.hex` file from STM32CubeIDE.

## Simulation Video
![Watch the video](https://github.com/MohamedElsayedd1/Mastering_Embededd_System/blob/main/6.%20MCU_Essential_Peripherals/Lesson_1_GPIO_Part1/GPIO_Lab1_STM32F103xx/GPIO_Lab1.gif)
[Watch the simulation video here](https://github.com/MohamedElsayedd1/Mastering_Embededd_System/blob/main/6.%20MCU_Essential_Peripherals/Lesson_1_GPIO_Part1/GPIO_Lab1_STM32F103xx/GPIO_Lab1.gif).
## License
This project is licensed under the BSD 3-Clause License. See LICENSE for details.
