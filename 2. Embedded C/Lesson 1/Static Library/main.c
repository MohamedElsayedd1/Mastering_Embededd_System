#include <stdio.h>
#include "UART.h"
#include "CAN.h"
#include "GPIO.h"

int main(){
    CAN_Init();
    UART_Init();
    GPIO_Init();
    return 0;
}