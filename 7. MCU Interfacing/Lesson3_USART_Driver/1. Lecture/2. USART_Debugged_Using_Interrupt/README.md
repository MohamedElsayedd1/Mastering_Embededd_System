### 1. **USART Driver With Interrupt Mode Test**

In interrupt mode, the USART communication is handled by interrupts. When data is received, the USART interrupt triggers and a callback function is used to process the data. This allows the CPU to perform other tasks until data is available.

![USART Interrupt]()

#### Code Example: `main.c` for Interrupt Mode

```c
#include "stm32f103x6.h"
#include "stm32f103x6_USART_driver.h"

USART_Config_t UART1_Config;

void clock_Init() {
    GPIOA_CLK_EN();  // Enable clock for GPIOA
    GPIOB_CLK_EN();  // Enable clock for GPIOB
    AFIO_CLK_EN();   // Enable clock for AFIO
}

void MyUSART_RecieveByte(void) {
    uint16 Received = MCAL_USART_RecieveByte(&UART1_Config);
    MCAL_USART_TransmitByte(&UART1_Config, Received);
}

int main(void) {
    UART1_Config = {
        .USARTx = USART1,
        .wordLength = USART_8_BIT_WORD_LENGTH,
        .parityMode = USART_DISABLED_PARITY,
        .paritySelect = USART_EVEN_PARITY,
        .stopBits = USART_1_STOP_BITS,
        .TxMode = USART_TX_ENABLED,
        .RxMode = USART_RX_ENABLED,
        .Tx_Interrupt_Enable = USART_TX_INTERRUPT_DISABLED,
        .Rx_Interrupt_Enable = USART_RX_INTERRUPT_ENABLED,
        .CTS_CTRL = USART_CTS_DISABLED,
        .RTS_CTRL = USART_RTS_DISABLED,
        .baud_rate = 115200,
        .USARTx_CallBackFunction = MyUSART_RecieveByte
    };

    // Initialize the clock and USART
    clock_Init();
    MCAL_USART_Init(&UART1_Config);

    while (1) {
        // Main loop does nothing, everything is handled by interrupts
    }
}
```

In interrupt mode, when data is received, the callback function `MyUSART_RecieveByte()` is executed, which echoes the received data.

## Functions

### Polling Mode Functions:
- **MCAL_USART_Init**: Initializes the USART peripheral with the provided configuration.
- **MCAL_USART_RecieveByte**: Receives a byte of data from the USART.
- **MCAL_USART_TransmitByte**: Sends a byte of data over the USART.

### Interrupt Mode Functions:
- **USART1_IRQHandler**: The interrupt handler function that is called when data is received on USART1. It calls the callback function set in the configuration structure.
- **MyUSART_RecieveByte**: A callback function that processes received data.