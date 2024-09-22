/* @Eng. Mohamed Elsayed */
/* startup.c */

#include <stdint.h>

#define STACK_TOP (uint32_t)0x20001000

extern int main(void);
extern uint32_t stack_top;

void Reset_Handler();
void NMI_Handler() __attribute__((weak, alias("Reset_Handler")));
void Hard_Fault_Handler()__attribute__((weak, alias("Reset_Handler")));
void Memory_Management_Fault_Handler()__attribute__((weak, alias("Reset_Handler")));
void Bus_Fault_Handler()__attribute__((weak, alias("Reset_Handler")));
void Usage_Fault_Handler()__attribute__((weak, alias("Reset_Handler")));

uint32_t Vector_Table[] __attribute__((section(".Vector_Table"))) = {
    (uint32_t) &stack_top,
    (uint32_t) Reset_Handler,
    (uint32_t) NMI_Handler,
    (uint32_t) Hard_Fault_Handler,
    (uint32_t) Memory_Management_Fault_Handler,
    (uint32_t) Bus_Fault_Handler,
    (uint32_t) Usage_Fault_Handler,
};

extern uint32_t _S_DATA; // Start of the .data section in SRAM
extern uint32_t _E_DATA; // End of the .data section in SRAM
extern uint32_t _E_TEXT; // Load address of the .data section in Flash
extern uint32_t _S_BSS;  // Start of the .bss section in SRAM
extern uint32_t _E_BSS;  // End of the .bss section in SRAM

void Reset_Handler(){
    uint32_t *src = &_E_TEXT;
    uint32_t *dest = &_S_DATA;

    // Copy data from Flash to SRAM until the end of .data section
    while(dest < &_E_DATA){
        *(uint32_t *)dest++ = *(uint32_t *)src++;
    }

    // Initialize the .bss section to zero
    dest = &_S_BSS;
    while(dest < &_E_BSS){
        *(uint32_t *)dest++ = 0;
    }

    main();
}
