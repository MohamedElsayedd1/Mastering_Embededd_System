ENTRY(reset)

MEMORY{
    Mem(rwx) : o = 0x00000000, l = 64M
}

SECTIONS{
    . = 0x10000;
    .startup . :
    {
        startup.o(.text)
    }>Mem
    .text :
    {
        *(.text)
    }>Mem
    .rodata : 
    {
        *(.rodata)
    }>Mem
    .data : 
    {
        *(.data)
    }>Mem
    .bss :
    {
        *(.bss) *(.comment)
    }>Mem
    . = . + 0x2000;
    stack_top = .;
}