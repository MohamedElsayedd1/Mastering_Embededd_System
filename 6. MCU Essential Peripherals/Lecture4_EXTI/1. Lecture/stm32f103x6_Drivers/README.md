## STM32F103x6 External Interrupt (EXTI) Driver

### Overview
This repository contains a fully configurable EXTI driver for STM32F103x6 microcontrollers. The driver allows the configuration and management of external interrupts on GPIO pins, supporting various trigger types and callback mechanisms.

---

### Features
- Configurable edge trigger: **Falling Edge**, **Rising Edge**, or **Both Edges**.
- Callback function support for custom interrupt handling.
- Simple APIs for initialization, deinitialization, and callback registration.
- Lightweight implementation for efficient operation.

---

### Files
- **`stm32f103x6_EXTI_driver.h`**: Header file defining driver structures, macros, and APIs.
- **`stm32f103x6_EXTI_driver.c`**: Implementation of the EXTI driver APIs and interrupt handlers.

---

### Usage
1. **Include the driver in your project**:
   ```c
   #include "stm32f103x6_EXTI_driver.h"
   ```

2. **Define a callback function**:
   ```c
   void MyInterruptHandler(void) {
       // Custom interrupt logic here
   }
   ```

3. **Configure and initialize the EXTI pin**:
   ```c
   EXTI_PinConfig_t PinConfig;
   PinConfig.port = GPIOA;
   PinConfig.pin.PinNum = GPIO_PIN_5;
   PinConfig.pin.Mode = GPIO_MODE_INPUT_FLOATING;
   PinConfig.trigger = EXTI_RISING_EDGE;
   PinConfig.CallBackFun = MyInterruptHandler;

   EXTI_Init(&PinConfig);
   ```

4. **Deinitialize the EXTI line when done**:
   ```c
   EXTI_Deinit(GPIO_PIN_5);
   ```

---

### Simulation
- The Proteus simulation demonstrates the EXTI functionality, triggering an interrupt on a GPIO pin.
  
 ![EXTI9_Trigger](https://github.com/MohamedElsayedd1/Mastering_Embededd_System/blob/main/6.%20MCU%20Essential%20Peripherals/Lecture4_EXTI/1.%20Lecture/stm32f103x6_Drivers/EXTI9_Trigger.gif)


---

### Debugging
- Use Keil uVision to debug the driver, analyze NVIC settings, and verify callback executions.
- **Debugging Screenshot**: `KeilMicroVisionDebug.png`
  
![KeilMicroVisionDebug](https://github.com/MohamedElsayedd1/Mastering_Embededd_System/blob/main/6.%20MCU%20Essential%20Peripherals/Lecture4_EXTI/1.%20Lecture/stm32f103x6_Drivers/KeilMicroVisionDebug.png)

---

### API Documentation

#### `void EXTI_Init(EXTI_PinConfig_t *PinConfig)`
Initializes the EXTI line with the specified configuration.
- **Parameters**:
  - `PinConfig`: Pointer to the EXTI pin configuration structure.

#### `void EXTI_Deinit(GPIO_PinNum_t PinNum)`
Deinitializes the specified EXTI line.

#### `void EXTI_SetCallback(GPIO_PinNum_t PinNum, void (*CallBackFun)(void))`
Registers a callback function for the specified EXTI line.

---

### Requirements
- **Microcontroller**: STM32F103x6 or compatible.
- **Toolchain**: Keil uVision, STM32CubeIDE, or equivalent.
- **Simulation**: Proteus 8.0 or later.

---

### Author
**Mohamed Elsayed**  
Email: [momaroof61@example.com]  
Date: December 1, 2024  
