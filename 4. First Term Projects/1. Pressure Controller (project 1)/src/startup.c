/* @Eng. Mohamed Elsayed */
/* startup.c */

#include <stdint.h>

extern int main();
extern uint32_t stack_top;

void ResetHandler();
void NMIHandler() __attribute__((weak, alias("ResetHandler")));
void HardFaultHandler() __attribute__((weak, alias("ResetHandler")));
void MemoryManagementFaultHandler() __attribute__((weak, alias("ResetHandler")));
void BusFaultHandler() __attribute__((weak, alias("ResetHandler")));
void UsageFaultHandler() __attribute__((weak, alias("ResetHandler")));

uint32_t vectorTable[] __attribute__((section(".Vactor_Table"))) = {
    &stack_top,
    (uint32_t) ResetHandler,
    (uint32_t) NMIHandler,
    (uint32_t) HardFaultHandler,
    (uint32_t) MemoryManagementFaultHandler,
    (uint32_t) BusFaultHandler,
    (uint32_t) UsageFaultHandler,
};

extern uint8_t _S_TEXT;
extern uint8_t _E_TEXT;
extern uint8_t _S_DATA;
extern uint8_t _E_DATA;
extern uint8_t _S_BSS;
extern uint8_t _E_BSS;

void ResetHandler() {
    // Copy .data section from flash to SRAM
    uint8_t *src = (uint8_t *)&_E_TEXT;
    uint8_t *dest = (uint8_t *)&_S_DATA;

    while (dest < (uint8_t *)&_E_DATA) {
        *dest++ = *src++;
    }

    // Zero initialize the .bss section
    dest = (uint8_t *)&_S_BSS;
    while (dest < (uint8_t *)&_E_BSS) {
        *dest++ = 0;
    }

    // Call main() function
    main();

    // Optionally: Loop forever in case main() returns (typically not expected in embedded systems)
    while (1);
}