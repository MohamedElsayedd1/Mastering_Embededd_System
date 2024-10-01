#ifndef _LIFO_H_
#define _LIFO_H_

// Include Header files
#include <stdint.h>

// LIFO type definition

typedef struct{
    uint32_t length; // Maximum number of elements that could be added
    uint32_t count; // number of elements added to the stack(LIFO)
    uint32_t *top; // pointer to last element (data of uint32_t) has been added 
    uint32_t *base; // pointer to first element (data of uint32_t) has been added
} stack_t;

typedef enum
{
    LIFO_OK,
    LIFO_EMPTY,
    LIFO_NOT_EMPTY,
    LIFO_FULL,
    LIFO_NOT_FULL,
    LIFO_NULL
} stack_status_t;

stack_status_t stackInit(stack_t *lifo, uint32_t *arr, uint32_t length);
stack_status_t stackPush(stack_t *lifo, uint32_t data);
stack_status_t stackPop(stack_t *lifo, uint32_t *data);
stack_status_t stackIsEmpty(stack_t *lifo);
stack_status_t stackIsFull(stack_t *lifo);
stack_status_t stackClear(stack_t *lifo);
stack_status_t stackDisplay(stack_t *lifo);
stack_status_t stackTop(stack_t *lifo, uint32_t *top);

#endif