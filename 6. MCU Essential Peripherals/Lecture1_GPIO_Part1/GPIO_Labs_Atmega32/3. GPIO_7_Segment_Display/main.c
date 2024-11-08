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
    DDRC = 0xFF;
}

gpio_state_t PC0_Btn_Prevstate = GPIO_LOW;
uint8_t _7Seg[] = {0b0000, 0b0001, 0b0010, 0b0011, 0b0100, 0b0101, 0b0110, 0b0111, 0b1000, 0b1001};

void main(){
    GPIO_Init();
    while(1){
        volatile uint8_t i = 0;
        volatile uint8_t j = 0;
        for (i = 0; i < 10; i++){
            PORTA &= ~(0b1111 << 4); 
            PORTA |= (_7Seg[i] << 4);
            for (j = 0; j < 10; j++){
                PORTA &= ~(0b1111 << 0); // clear Highest 4 bits
                PORTA |= (_7Seg[j] << 0);
                myDelay(5000);
            }
        }
    }

    return 0;
}