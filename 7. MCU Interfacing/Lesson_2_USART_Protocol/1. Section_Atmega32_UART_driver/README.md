
# ATmega32 UART and LCD Project

### **Description**
This project demonstrates the use of UART communication and an LCD module with the ATmega32 microcontroller. The program initializes UART with a baud rate of 9600 and sends a test string ("Testing UART") to both the UART interface and an LCD display. 

![UART Testing]()

### **Features**
- UART communication with customizable configurations (baud rate, data bits, stop bits, parity, and mode).
- LCD integration to display messages sent via UART.
- Modular driver support for GPIO, LCD, and UART.

---

### **Components Used**
1. **Microcontroller**: ATmega32
2. **LCD**: 16x2 character LCD module
3. **UART**: Standard UART communication for data transmission
4. **Software Libraries**:
   - `atmega32_GPIO_driver.h` (GPIO functions)
   - `atmega32_HAL_LCD.h` (LCD initialization and control)
   - `atmega32_UART_driver.h` (UART configuration and data transmission)

---

### **Hardware Requirements**
- ATmega32 Microcontroller
- 16x2 LCD Module
- UART Communication Interface
- Resistors and capacitors for stable operation
- Power supply (5V)
- Connecting wires

---

### **Software Requirements**
- **IDE**: Atmel Studio / Microchip Studio
- **Compiler**: AVR-GCC
- **Libraries**: AVR Libc for utilities such as `_delay_ms()`.

---

### **Connections**
| ATmega32 Pin | Peripheral   | Description         |
|--------------|--------------|---------------------|
| `PORTD`      | LCD Data     | 8-bit data pins for LCD |
| `RS`, `E`    | LCD Control  | Control lines (RS and Enable) |
| `TX (PD1)`   | UART TX      | UART Transmit Pin   |
| `RX (PD0)`   | UART RX      | UART Receive Pin    |
| `VCC`, `GND` | Power Supply | 5V DC for peripherals |

---

### **Setup and Configuration**
1. **UART Configuration**:
   - Baud Rate: 9600
   - Data Bits: 8
   - Stop Bits: 1
   - Parity: None
   - Mode: Asynchronous

2. **LCD Initialization**:
   - 16x2 character LCD in 4-bit mode.

3. **Drivers**:
   - **GPIO**: Handles general-purpose I/O pins for LCD.
   - **LCD HAL**: Abstracts LCD operations such as initialization and string display.
   - **UART**: Configures UART and handles string transmission.

---

### **Code Walkthrough**

#### **Main Application**
```c
#include <util/delay.h>
#include <xc.h>

#include "atmega32_GPIO_driver.h"
#include "atmega32_HAL_LCD.h"
#include "atmega32_UART_driver.h"

// Define a UART configuration instance
UART_config_t myUart = {
    .baud_rate = 9600,                 // Baud rate
    .data_bits = UART_8_BIT_DATA,      // 8 data bits
    .stop_bits = UART_ONE_STOP_BIT,    // 1 stop bit
    .parity_type = UART_NO_PARITY,     // No parity
    .mode = UART_ASYNC_MODE,           // Asynchronous mode
    .rx_enable_interrupt = UART_ENABLE_INTERRUPT,  // RX interrupt enabled
    .tx_enable_interrupt = UART_DISABLED_INTERRUPT // TX interrupt disabled
};

int main(void) {
    // Initialize LCD
    lcd_initialize();

    // Initialize UART
    UART_Init(&myUart);

    // Test string to display and transmit
    uint8_t buff[] = "Testing UART\n";

    // Display message on LCD
    lcd_send_string(buff);

    // Transmit message via UART
    UART_TransmitString(buff);

    // Infinite loop
    while (1) {
        // Add additional functionality here
    }

    return 0;
}
```

### **Author**
**Mohamed Elsayed**  
*Embedded Systems Developer*  
Date: 05/12/2024
