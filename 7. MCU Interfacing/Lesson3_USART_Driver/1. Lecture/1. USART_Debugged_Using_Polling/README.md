

### 1. **USART Driver With Polling Mode Test**

In this mode, the USART communication is done by constantly checking the status of the USART registers in a loop. The main program waits for data to be received and then transmits it.

![USART Polling](https://github.com/MohamedElsayedd1/Mastering_Embededd_System/blob/main/7.%20MCU%20Interfacing/Lesson3_USART_Driver/1.%20Lecture/1.%20USART_Debugged_Using_Polling/KeilMicroVission_Debuging_Pulling.png)

#### Code Example: `main.c` for Polling Mode

```c
#include "stm32f103x6.h"
#include "stm32f103x6_USART_driver.h"

USART_Config_t UART1_Config;

void clock_Init() {
    GPIOA_CLK_EN();  // Enable clock for GPIOA
    GPIOB_CLK_EN();  // Enable clock for GPIOB
    AFIO_CLK_EN();   // Enable clock for AFIO
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
        .Rx_Interrupt_Enable = USART_RX_INTERRUPT_DISABLED,
        .CTS_CTRL = USART_CTS_DISABLED,
        .RTS_CTRL = USART_RTS_DISABLED,
        .baud_rate = 115200
    };

    // Initialize the clock and USART
    clock_Init();
    MCAL_USART_Init(&UART1_Config);

    while (1) {
        uint16 DataReceived = MCAL_USART_RecieveByte(&UART1_Config);
        MCAL_USART_TransmitByte(&UART1_Config, DataReceived);
    }
}
```

In this example, the program continuously receives data from USART1 and immediately sends it back (echo).
