#include "UART.h"

void UART_Send_Byte(uint8_t byte){
    UARTDR_REG = byte;
}

void UART_Send_String(uint8_t *str){
    while(str != '\0'){
        UART_Send_Byte(*(uint8_t*)str);
        str++;
    }
}