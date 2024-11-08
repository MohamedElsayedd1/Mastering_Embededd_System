#include "MemMap.h"

#define MCU_CLK_FREQ            1000000UL

#define SET_BIT(REG,BIT_POS)    (REG |= (1 << BIT_POS))
#define RESET_BIT(REG,BIT_POS)  (REG &= ~(1 << BIT_POS))
#define TOGGLE_BIT(REG,BIT_POS) (REG ^= (1 << BIT_POS))
#define READ_BIT(REG,BIT_POS)   ((REG >> BIT_POS) & 0x01)

void myDelay(uint32_t delay){
    while(delay--);
}

void GPIO_Init(){
    DDRA = 0xFF;
}

void main(){
    GPIO_Init();
    while(1){
        SET_BIT(PORTA, 0);
        myDelay(10000);
        SET_BIT(PORTA, 1);
        myDelay(10000);
        SET_BIT(PORTA, 2);
        myDelay(10000);
        SET_BIT(PORTA, 3);
        myDelay(10000);
        SET_BIT(PORTA, 4);
        myDelay(10000);
        SET_BIT(PORTA, 5);
        myDelay(10000);
        SET_BIT(PORTA, 6);
        myDelay(10000);
        SET_BIT(PORTA, 7);
        myDelay(10000);

        RESET_BIT(PORTA, 7);
        myDelay(10000);
        RESET_BIT(PORTA, 6);
        myDelay(10000);
        RESET_BIT(PORTA, 5);
        myDelay(10000);
        RESET_BIT(PORTA, 4);
        myDelay(10000);
        RESET_BIT(PORTA, 3);
        myDelay(10000);
        RESET_BIT(PORTA, 2);
        myDelay(10000);
        RESET_BIT(PORTA, 1);
        myDelay(10000);
        RESET_BIT(PORTA, 0);
        myDelay(10000);
    }

    return 0;
}