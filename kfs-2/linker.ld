ENTRY(_start)

PHDRS
{
	rodata PT_LOAD FLAGS(4); /* R only */
	data PT_LOAD FLAGS(6); /* R + W */
    text PT_LOAD FLAGS(5); /* R + X */
    gdt PT_LOAD FLAGS(6);
}

SECTIONS
{
	.gdt 0x00000800:
    {
        *(.gdt)
    } : gdt

	. = 1M;

    .boot :
    {
        *(.multiboot)
    } : text
	
	.text BLOCK(4K) : ALIGN(4K)
	{
		*(.multiboot)
		*(.text)
	} : text

	.rodata BLOCK(4K) : ALIGN(4K)
	{
		*(.rodata)
	} : rodata

	.data BLOCK(4K) : ALIGN(4K)
	{
		*(.data)
	} : data

	.bss BLOCK(4K) : ALIGN(4K)
	{
		*(COMMON)
		*(.bss)
	} : data

    . = ALIGN(16);
    stack_bottom = .;
    . += 0x4000;
    stack_top = .;
}
