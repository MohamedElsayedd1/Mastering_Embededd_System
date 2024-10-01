#include <stdio.h>
#include "LIFO.h"

#define UART_BUFFER_LEGNTH  5

uint32_t UART_Buffer[UART_BUFFER_LEGNTH];
stack_t UART_LIFO;

int main(){
    uint32_t stack_top;

    if(stackInit(&UART_LIFO, UART_Buffer, UART_BUFFER_LEGNTH) == LIFO_OK){
        printf("UART LIFO has been intialized\n");
    }

    uint32_t popData;
    // Popping 1 element 
    if(stackPop(&UART_LIFO, &popData) == LIFO_OK){
        printf("Value %d is popped from the UART LIFO.\n", popData);
    }
    else{
        printf("UART LIFO is EMPTY already, can't pop any data.\n");
    }

    uint32_t pushData = 30;
    // Pushing data to stack
    for (int i = 0; i < 6; i++){
        if (stackPush(&UART_LIFO, pushData++) == LIFO_OK)
        {
            printf("Value %d is pushed to the UART LIFO.\n", pushData);
        }
        else{
            printf("UART LIFO is FULL already, can't push any data.\n");
        }
    }

    // Print Stack
    stackDisplay(&UART_LIFO);

    // Get stack top
    stackTop(&UART_LIFO, &stack_top);

    printf("---------------Stack Top--------------\n\n");
    printf("Stack top = %d\n\n", stack_top);
    printf("--------------------------------------\n\n");

    // Popping data from stack
    for (int i = 0; i < 6; i++){
        if(stackPop(&UART_LIFO, &popData) == LIFO_OK){
            printf("Value %d is popped from the UART LIFO.\n", popData);
        }
        else{
            printf("UART LIFO is EMPTY already, can't pop any data.\n");
        }
    }

    // Pushing data to stack
    for (int i = 0; i < 6; i++){
        if (stackPush(&UART_LIFO, pushData++) == LIFO_OK)
        {
            printf("Value %d is pushed to the UART LIFO.\n", pushData);
        }
        else{
            printf("UART LIFO is FULL already, can't push any data.\n");
        }
    }

    // Clear and remove all elements from the stack
    stackClear(&UART_LIFO);

    // Popping 1 element 
    if(stackPop(&UART_LIFO, &popData) == LIFO_OK){
        printf("Value %d is popped from the UART LIFO.\n", popData);
    }
    else{
        printf("UART LIFO is EMPTY already, can't pop any data.\n");
    }

    // Print Stack
    stackDisplay(&UART_LIFO);

    // Get stack top
    stackTop(&UART_LIFO, &stack_top);
    return 0;
}

