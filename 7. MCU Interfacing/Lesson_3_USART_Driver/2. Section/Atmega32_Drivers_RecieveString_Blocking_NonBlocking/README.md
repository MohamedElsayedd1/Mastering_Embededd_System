## USART Receive String Repository (Blocking and Non-Blocking with Interrupt)

### Overview
This repository demonstrates how to **receive strings** using USART communication in two modes:
1. **Blocking Mode**: Uses a polling mechanism to receive a string character by character until a termination condition is met.
2. **Non-Blocking Mode**: Uses an **Interrupt Service Routine (ISR)** to receive characters asynchronously and store them in a buffer.

---

### Features
1. **USART Blocking String Reception**:
   - Reads characters using polling until a termination character (`'\n'` or `'\r'`) is received.
   - Prevents buffer overflow by enforcing a maximum buffer size.
   - Null-terminates the string for safe string handling.

2. **USART Non-Blocking String Reception**:
   - Utilizes USART RX Interrupts to receive characters in the background.
   - Handles string reception asynchronously without blocking the main program.
   - Supports buffer management and null-termination.

---

### Code Details

#### 1. Blocking Mode: `USART_ReceiveString` Function

This function uses polling to wait for each character until the termination condition is met (`'\n'` or `'\r'`).

**Implementation:**

```c
void USART_ReceiveString(char *buffer, uint16_t max_length) {
    uint16_t index = 0;  // Buffer index
    char received_char;

    while (1) {
        received_char = UART_ReceiveByte();  // Blocking call to receive one byte

        if (received_char == '\n' || received_char == '\r') {
            buffer[index] = '\0';  // Null-terminate the string
            break;
        }

        if (index < (max_length - 1)) {
            buffer[index++] = received_char;  // Add character to buffer
        } else {
            buffer[index] = '\0';  // Prevent buffer overflow
            break;
        }
    }
}
```

**How It Works**:
- Continuously calls `UART_ReceiveByte()` to receive a single character.
- Stops receiving on `'\n'` (newline) or `'\r'` (carriage return).
- Ensures the buffer is null-terminated for proper string handling.
- Avoids buffer overflow by checking the `max_length`.

---

#### 2. Non-Blocking Mode: USART RX ISR

The ISR handles incoming characters **asynchronously** and stores them in a buffer.

**Global Variables**:
```c
#define BUFFER_SIZE 100

volatile char uart_buffer[BUFFER_SIZE];  // Buffer to store received string
volatile uint16_t buffer_index = 0;      // Index for buffer
```

**ISR Implementation**:

```c
ISR(USART_RXC_vect) {
    char received_char = UART_ReceiveByte();

    // Check for termination or buffer overflow
    if (received_char == '\n' || received_char == '\r' || buffer_index >= BUFFER_SIZE - 1) {
        uart_buffer[buffer_index] = '\0';  // Null-terminate the string
        buffer_index = 0;                 // Reset buffer index

        // Optional: Display string on LCD (example for debugging)
        lcd_send_string_pos("                    ", 2, 1);  // Clear line
        lcd_send_string_pos(uart_buffer, 2, 1);            // Display received string
    } else {
        uart_buffer[buffer_index++] = received_char;  // Store character
    }
}
```

**How It Works**:
- The ISR is triggered when a character is received via USART.
- Characters are stored in a global buffer.
- Stops receiving when:
  - A termination character (`'\n'` or `'\r'`) is received.
  - The buffer is full.
- Automatically null-terminates the string for safe string handling.

---

### Usage

1. **Blocking Mode**:
   - Call the `USART_ReceiveString` function to receive a string in a blocking manner.

```c
#define BUFFER_SIZE 100

char buffer[BUFFER_SIZE];
USART_ReceiveString(buffer, BUFFER_SIZE);
USART_TransmitString(buffer);  // Echo back for testing
```

2. **Non-Blocking Mode**:
   - Enable USART RX interrupt and define the ISR.

```c
// Enable USART RX Interrupt
UCSRB |= (1 << RXCIE);

// Global Interrupt Enable
sei();

// ISR will automatically handle incoming data
```

---

### Requirements
- **Microcontroller**: STM32F103 (or compatible MCU)
- **USART Driver**: Pre-existing USART driver (functions like `UART_ReceiveByte()` and `UART_TransmitString()`).
- **IDE/Toolchain**: STM32CubeIDE, Keil, or any ARM-compatible compiler.
- **Optional**: LCD Driver for string display.

---

### Example Workflow
1. Initialize USART with appropriate configurations.
2. Use either the **blocking** or **non-blocking** method to receive strings.
3. For non-blocking mode:
   - Enable the RX interrupt.
   - Implement the ISR to handle incoming characters.
4. Test by echoing the received string back to a terminal.

---

### Testing
1. Connect the USART pins to a serial terminal (e.g., PuTTY, RealTerm).
2. Send strings ending with `\n` or `\r` to the microcontroller.
3. For blocking mode:
   - The function waits until the full string is received.
4. For non-blocking mode:
   - Strings are received asynchronously and displayed on an LCD or sent back to the terminal.

---

### Notes
- **Blocking Mode** is simpler but halts program execution until a string is fully received.
- **Non-Blocking Mode** is ideal for multitasking and real-time applications.
- Buffer overflow protection ensures safe string handling.

---

### Future Improvements
- Implement DMA-based USART reception for enhanced efficiency.
- Add support for dynamic buffer allocation.

---

### Author
**Mohamed Elsayed**  
Embedded Systems Developer  
