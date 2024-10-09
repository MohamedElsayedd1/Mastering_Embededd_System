#include "LIFO.h"

stack_status_t stackInit(stack_t *lifo, uint32_t *arr, uint32_t length){
    if(lifo == NULL || arr == NULL){
        printf("Trying to access NULL pointer !\n");
        return LIFO_NULL;
    }
    if(arr != NULL){
        lifo->count = 0;
        lifo->length = length;
        lifo->top = (uint32_t *)arr;
        lifo->base = (uint32_t *)arr;
        return LIFO_OK;
    }
    return LIFO_NULL;
}

stack_status_t stackPush(stack_t *lifo, uint32_t data){
    if(!lifo->top || !lifo->base){
        printf("Trying to access NULL pointer !\n");
        return LIFO_NULL;
    }
    if(stackIsFull(lifo) == LIFO_NOT_FULL){
        *(lifo->top) = data;
        lifo->count++;
        lifo->top++;
        return LIFO_OK;
    }
    return LIFO_FULL;
}

stack_status_t stackPop(stack_t *lifo, uint32_t *data){
    if(!lifo->top || !lifo->base){
        printf("Trying to access NULL pointer !\n");
        return LIFO_NULL;
    }
    if(stackIsEmpty(lifo) == LIFO_NOT_EMPTY){
        lifo->top--; // Move the top pointer first, then access the value
        *data = *(lifo->top); // Store the popped value in *data
        lifo->count--;
        return LIFO_OK;
    }
    return LIFO_EMPTY;
}

stack_status_t stackIsEmpty(stack_t *lifo){
    if(!lifo->top || !lifo->base){
        printf("Trying to access NULL pointer !\n");
        return LIFO_NULL;
    }
    return lifo->count == 0 ? LIFO_EMPTY : LIFO_NOT_EMPTY;
}

stack_status_t stackIsFull(stack_t *lifo){
    if(!lifo->top || !lifo->base){
        printf("Trying to access NULL pointer !\n");
        return LIFO_NULL;
    }
    return lifo->count == lifo->length ? LIFO_FULL : LIFO_NOT_FULL;
}

stack_status_t stackClear(stack_t *lifo){
    if(!lifo->top || !lifo->base){
        printf("Trying to access NULL pointer !\n");
        return LIFO_NULL;
    }
    while(stackIsEmpty(lifo) != LIFO_EMPTY){
        uint32_t temp;
        stack_status_t stack_status = stackPop(lifo, &temp);
    }
    return LIFO_EMPTY;
}

stack_status_t stackDisplay(stack_t *lifo){
    if(!lifo->top || !lifo->base){
        printf("Trying to access NULL pointer !\n");
        return LIFO_NULL;
    }

    if(stackIsEmpty(lifo) == LIFO_NOT_EMPTY){
        uint32_t *traverse_ptr = (uint32_t *)(lifo->top);
        traverse_ptr--; // Move the top pointer first, then access the value
        printf("-------------- Stack(LIFO) -------------\n");
        while(traverse_ptr >= (uint32_t *)(lifo->base)){
            printf("\t%d\n", *traverse_ptr--);
        }
        printf("\n--------------------------------------\n");
        return LIFO_OK;
    }
    else{
        printf("-------------- Stack(LIFO) -------------\n");
        printf("\tStack is empty!\n");
        printf("\n--------------------------------------\n");
        return LIFO_EMPTY;
    }
    
}

stack_status_t stackTop(stack_t *lifo, uint32_t *top){
    if(!lifo || !top){
        printf("Trying to access NULL pointer !\n");
        return LIFO_NULL;
    }

    if(stackIsEmpty(lifo) != LIFO_EMPTY){
        *top = *(lifo->top - 1);
        return LIFO_OK;
    }
    else{ // Stack is empty, there's no top
        printf("Stack is already empty, there's no top!\n");
        return LIFO_EMPTY;
    }
}