#include "MemMap.h"

#define MCU_CLK_FREQ            1000000UL

#define SET_BIT(REG,BIT_POS)    (REG |= (1 << BIT_POS))
#define RESET_BIT(REG,BIT_POS)  (REG &= ~(1 << BIT_POS))
#define TOGGLE_BIT(REG,BIT_POS) (REG ^= (1 << BIT_POS))
#define READ_BIT(REG,BIT_POS)   ((REG >> BIT_POS) & 0x01)

typedef enum
{
    GPIO_LOW,
    GPIO_HIGH
} gpio_state_t;

void myDelay(uint32_t delay){
    while(delay--);
}

void GPIO_Init(){
    DDRA = 0xFF;
    // Set PC0 as input & Tri-state
    RESET_BIT(DDRC, 0);
    RESET_BIT(PORTC, 0);
}

gpio_state_t PC0_Btn_Prevstate = GPIO_LOW;
uint32_t ledCounter = 0;

void main(){
    GPIO_Init();
    while(1){
        gpio_state_t PC0_Btn_Currstate = READ_BIT(PINC, 0);
        if(PC0_Btn_Prevstate == GPIO_LOW && PC0_Btn_Currstate == GPIO_HIGH){
            TOGGLE_BIT(PORTA, ledCounter++);
            if(ledCounter >= 8){
                ledCounter = 0;
            }
        }
        PC0_Btn_Prevstate = PC0_Btn_Currstate;
    }

    return 0;
}
