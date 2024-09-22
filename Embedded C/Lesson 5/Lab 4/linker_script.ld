/* @Eng. Mohamed Elsayed */
/* linker_script.ld */

ENTRY(Vector_Table)

MEMORY{
    FLASH(rx) : ORIGIN = 0x08000000, LENGTH = 128k
    SRAM(rwx) : ORIGIN = 0x20000000, LENGTH = 20k
}

_heap_size = 1024; /* 1KB of heap */
_stack_size = 2048; /* 2KB of stack */ 


SECTIONS{
    .text : 
    {
        _S_TEXT = .;
        *(.Vector_Table*)
        *(.text*)
        *(.rodata)
        _E_TEXT = .;
    }> FLASH
    .data : 
    {
        _S_DATA = .;
        *(.data)
        _E_DATA = .;
    }>SRAM AT> FLASH
    .bss : 
    {
        _S_BSS = .;
        *(.bss)
        _E_BSS = .;
    }>SRAM
    .heap :
    {
        _S_HEAP = .;
        . = . + _heap_size;
        _E_HEAP = .;
    }>SRAM
    .stack : 
    {
        _S_STACK = .;
        . = . + _stack_size;
        stack_top = .;
    }>SRAM
    
    /* proper alignment for all sections */
    . = ALIGN(4);
}