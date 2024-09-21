

MEMORY{
    FLASH(rx) : ORIGIN = 0x00000000, LENGTH = 512M
    SRAM(rwx) : ORIGIN = 0x20000000, LENGTH = 512M
}

SECTIONS{
    .text : 
    {
        *(.Vector_Table)
        *(.text)
        *(.rodata)
        _E_TEXT = .;
    }>FLASH
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

    . = ALIGN(4);
}