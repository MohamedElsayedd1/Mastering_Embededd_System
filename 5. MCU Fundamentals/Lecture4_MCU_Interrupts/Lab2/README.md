# Atmel Studio Lab - External Interrupt Trigger Simulation

This project demonstrates how to configure and handle external interrupts on an ATmega32 microcontroller using Atmel Studio. The project is designed to trigger specific external interrupts (INT0, INT1, INT2) and toggle the states of connected LEDs on pins `PD4`, `PD5`, and `PD6`. This can be tested and debugged in Atmel Studio's simulation mode and simulated further in Proteus.

---

## Project Overview

- **Microcontroller**: ATmega32
- **IDE**: Atmel Studio
- **Simulation Tool**: Proteus
- **Interrupts**: INT0, INT1, INT2
- **Peripherals**: LEDs on `PD4`, `PD5`, and `PD6`

### Files Included

- **TriggerExternalInterrupt.c** - Contains the code for setting up GPIO and external interrupts.
- **Proteus Simulation File** - A `.pdsprj` file for testing the project in Proteus.

---

## Project Setup

1. **Clone the Repository**:
   ```bash
   git clone <repo_link>
   ```
2. **Open the Project in Atmel Studio**:
   - Open `TriggerExternalInterrupt.atsln` in Atmel Studio.
   
3. **Build the Project**:
   - Click on `Build > Build Solution` or press `F7` to compile the code.

4. **Run Simulation**:
   - Start debugging in Atmel Studio to simulate external interrupt behavior.
   - In simulation mode, you can monitor register changes and LED toggling on `PD4`, `PD5`, and `PD6` when interrupts are triggered.

---

## External Interrupt Setup

### Interrupt Configuration

- **INT0**: Configured for a low-level trigger.
- **INT1**: Configured for a rising-edge trigger.
- **INT2**: Configured for a falling-edge trigger.

Each interrupt, when triggered, toggles its respective LED:
- **INT0** - Toggles `PD4`
- **INT1** - Toggles `PD5`
- **INT2** - Toggles `PD6`

---

## Links

- **Atmel Studio Debugging & Simulation Documentation**: [Atmel Studio Debugging Guide](https://drive.google.com/file/d/1oiH3Tt2XbOQzoKY_gMD4thkiAvAfkNw8/view?usp=drive_link)
- **Proteus Simulation File**: [Proteus Simulation Project](https://drive.google.com/file/d/1EbBEfCcv2wuAZOn6NAb5Vlbs2G2IG69K/view?usp=drive_link)

---

## Screenshots

### Proteus Simulation
[Proteus Simulation](https://drive.google.com/drive/folders/13ZylAy0OSQ0c7LeScVkDQDupXblbC-If)

---

## Usage

1. **Simulate External Interrupts**:
   - Use Atmel Studio to simulate the program in debug mode. Check that each interrupt handler toggles the expected LED.
   
2. **Proteus Simulation**:
   - Load the `.pdsprj` file in Proteus.
   - Run the simulation to observe LED toggling behavior when external signals trigger INT0, INT1, and INT2.

---

## License

This project is licensed under the MIT License.
```

### Instructions for Populating the README

- **Replace `<repo_link>`** with your actual repository link.
- **Update placeholder links** (e.g., `Atmel Studio Debugging Guide` and `Proteus Simulation Project`) with the real URLs if available.
- **Add screenshots** to the `screenshots` folder in your repository and use the correct paths in the README. 

This structure will give clear guidance on using the project and viewing the simulation results.
