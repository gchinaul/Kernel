/* linker for entry point */

ENTRY(_start)

PHDRS
{
    text PT_LOAD FLAGS(5); /* R + X */
    data PT_LOAD FLAGS(6); /* R + W */
    gdt PT_LOAD FLAGS(6);
}

SECTIONS {

    
    .gdt 0x00000800:
    {
        *(.gdt)
    } : gdt


    . = 1M;
    .boot :
    {
        *(.multiboot_header)
    } : text

    .text :
    {
        *(.text)

    } : text

    .bss :
    {
        *(.bss)
        *(COMMON)
    } : data

    . = ALIGN(16);
    stack_bottom = .;
    . += 0x4000;
    stack_top = .;
}
