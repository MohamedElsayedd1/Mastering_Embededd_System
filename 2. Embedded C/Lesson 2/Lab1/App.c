#include "UART.h"

uint8_t Data[] = "Learn-In-Depth : Mohamed Elsayed\n";
const int constant = 10;

int main(){
    UART_Send_String(Data);
    return 0;
}