/* @Eng. Mohamed Elsayed */
/* linkerscript.ld */

ENTRY(vectorTable)

MEMORY{
    FLASH(rx) : ORIGIN = 0x08000000, LENGTH = 128k
    SRAM(rwx) : ORIGIN = 0X20000000, LENGTH = 20k
}

_heap_size = 2048; /* 2KB of heap */
_stack_size = 2048; /* 2KB of stack */

SECTIONS{
    .text : {
        _S_TEXT = .;
        *(.Vactor_Table)
        *(.text*)
        *(.rodata)
        _E_TEXT = .;
    }>FLASH
    .data : {
        _S_DATA = .;
        *(.data)
        _E_DATA = .;
    }>SRAM AT> FLASH
    .bss : {
        _S_BSS = .;
        *(.bss)
        _E_BSS = .;
    }>SRAM
    .heap : {
        _S_HEAP = .;
        . = . + _heap_size;
        _E_HEAP = .;
    }>SRAM
    .stack : {
        _S_STACK = .;
        . = . + _stack_size;
        stack_top = .;
        _E_STACK = .;
    }>SRAM
    . = ALIGN(4);
}