#include "ksh.h"
#include "terminal.h"
#include "cursor.h"

static void the_banner(void)
{
	int i = 0;

	while (i++ < 9)
		kprintf("\n");

	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_MAGENTA, VGA_COLOR_BLACK);
	kprintf(CRASHOS_LINE1);
	kprintf(CRASHOS_LINE2);
	kprintf(CRASHOS_LINE3);
	kprintf(CRASHOS_LINE4);
	kprintf(CRASHOS_LINE5);

	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	kprintf(CRASHOS_SEP);

	terminal_color = vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
	kprintf(CRASHOS_INFO);

	terminal_color = vga_entry_color(VGA_COLOR_DARK_GREY, VGA_COLOR_BLACK);
	kprintf(CRASHOS_SEP);
}

void kmain(void)
{
	terminal_init();
	enable_cursor(0, 15);
	the_banner();

	
	stack_trace();

	gdt_init();
	idt_init();
	
	__asm__ volatile("sti");

	while (1)
		__asm__ volatile("hlt");
}
