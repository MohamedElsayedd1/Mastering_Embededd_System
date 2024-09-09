#ifndef _UART_H_
#define _UART_H_

typedef unsigned int uint32_t;
typedef volatile unsigned int vuint32_t;
typedef unsigned char uint8_t;
typedef volatile unsigned char vuint8_t;

#define UARTDR_REG *((vuint8_t * const)(0X101F1000))

void UART_Send_Byte(uint8_t byte);
void UART_Send_String(uint8_t *str);

#endif // !_UART_H_