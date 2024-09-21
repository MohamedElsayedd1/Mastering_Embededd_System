
#include <stdint.h>

extern int main(void);
extern uint32_t _E_TEXT;
extern uint32_t _S_DATA;
extern uint32_t _E_DATA;
extern uint32_t _S_BSS;
extern uint32_t _E_BSS;
extern uint32_t stack_top;

void Reset_Handler();
void NMI_Handler()__attribute__ ((weak, alias("Reset_Handler")));
void Hard_Fault_Handler()__attribute__ ((weak, alias("Reset_Handler")));
void Memory_Management_Fault_Handler()__attribute__ ((weak, alias("Reset_Handler")));
void Bus_Fault_Handler()__attribute__ ((weak, alias("Reset_Handler")));
void Usage_Fault_Handler()__attribute__ ((weak, alias("Reset_Handler")));

// Reserving 1024B in .bss by allocating 256 element, each element consume 4 bytes
static uint32_t Stack_top[256];

// Array of pointers to functions that takes nothing and return void
void (* const _Vector_table[6])() __attribute__((section(".Vector_Table"))) = {
    (void (*)())(Stack_top + 256),
    NMI_Handler,
    Hard_Fault_Handler,
    Memory_Management_Fault_Handler,
    Bus_Fault_Handler,
    Usage_Fault_Handler
};

void Reset_Handler(){
    uint8_t *src = (uint8_t *)&_E_TEXT;
    uint8_t *dest = (uint8_t *)&_S_DATA;

    while(dest < &_E_DATA){
        *dest++ = *src++;
    }

    dest = (uint8_t *)&_S_BSS;
    while(dest < &_E_BSS){
        *dest++ = 0;
    }

    main();

	
}