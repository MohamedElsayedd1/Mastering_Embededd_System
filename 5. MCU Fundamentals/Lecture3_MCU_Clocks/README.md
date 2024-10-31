
# MCU Clock Configuration Labs

This repository contains two labs that configure the clock frequencies of an STM32-based microcontroller. Both labs use the internal HSI (High-Speed Internal) RC oscillator as the system clock (SYSCLK) source.

## Lab 1: Clock Configuration with 8 MHz SysClk

### Objective

Configure the microcontroller to achieve the following clock frequencies:
- **SYSCLK (System Clock)**: 8 MHz
- **AHB (HCLK)**: 8 MHz
- **APB1 (PCLK1)**: 4 MHz
- **APB2 (PCLK2)**: 2 MHz

### Configuration Steps
1. Use the internal **HSI RC oscillator** (8 MHz) as the system clock source.
2. Set **AHB prescaler** to 1 (HCLK = SYSCLK / 1 = 8 MHz).
3. Set **APB1 prescaler** to 2 (PCLK1 = HCLK / 2 = 4 MHz).
4. Set **APB2 prescaler** to 4 (PCLK2 = HCLK / 4 = 2 MHz).

### Code (Keil Microvision Project)
The code for this lab can be found [here](link to Keil project in Google Drive).

### Simulation Results
- [Keil uVision Simulation Results for Lab 1](https://drive.google.com/file/d/1nKrNpL32qAz6ZukiwD41icxz-qnhAUpf/view?usp=drive_link)

---

## Lab 2: Clock Configuration with 32 MHz SysClk

### Objective

Configure the microcontroller to achieve the following clock frequencies:
- **SYSCLK (System Clock)**: 32 MHz
- **AHB (HCLK)**: 32 MHz
- **APB1 (PCLK1)**: 16 MHz
- **APB2 (PCLK2)**: 8 MHz

### Configuration Steps
1. Use the internal **HSI RC oscillator** (8 MHz) as the system clock source.
2. Configure the **PLL (Phase-Locked Loop)** to multiply the HSI clock by 4 to achieve 32 MHz SYSCLK.
3. Set **AHB prescaler** to 1 (HCLK = SYSCLK / 1 = 32 MHz).
4. Set **APB1 prescaler** to 2 (PCLK1 = HCLK / 2 = 16 MHz).
5. Set **APB2 prescaler** to 4 (PCLK2 = HCLK / 4 = 8 MHz).

### Code (Keil Microvision Project)
The code for this lab can be found [here](link to Keil project in Google Drive).

### Simulation Results
- [Keil uVision Simulation Results for Lab 2](https://drive.google.com/file/d/1eYaYMIzOlmiqNwIRP8uWFTaTo94Ry76W/view?usp=drive_link)

---

## Additional Resources
- [Learn In Depth - Embedded Systems Course](https://www.learn-in-depth.com/)
- [Facebook Embedded Systems Group](https://www.facebook.com/groups/embedded.system.KS/)
- [Mastering Embedded System Online Diploma](https://www.learn-in-depth.com/)

---

## How to Run
1. Clone or download the repository.
2. Open the Keil project for each lab and compile it.
3. Program your STM32-based development board using ST-Link or other available methods.
4. View the results using Keil uVision or an oscilloscope for real hardware measurements.

---

## License
This project is licensed under the **BSD 3-Clause License**. You may obtain a copy of the license at:
[opensource.org/licenses/BSD-3-Clause](https://opensource.org/licenses/BSD-3-Clause).

---

## Author
- **Mohamed Elsayed**  
  _Mastering Embedded Systems online diploma_

