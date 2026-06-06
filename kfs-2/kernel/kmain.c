#include "kernel.h"

extern ui8_t term_color;

void display_banner(void)
{
	int i = 0;

	while (i++ < 3)
		kernel_printf("\n");

	term_color = vga_entry_color(VGA_COLOR_LIGHT_MAGENTA, VGA_COLOR_BLACK);
	kernel_printf(BANNER_LINE1);
	kernel_printf(BANNER_LINE2);
	kernel_printf(BANNER_LINE3);
	kernel_printf(BANNER_LINE4);
	kernel_printf(BANNER_LINE5);
    
	term_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	kernel_printf(BANNER_SEP);

	term_color = vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
	kernel_printf(BANNER_INFO);

	term_color = vga_entry_color(VGA_COLOR_DARK_GREY, VGA_COLOR_BLACK);
	kernel_printf(BANNER_SEP);
}

int kmain(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    // Init GDT
    gdt_init();

    // Init drivers
    term_init();
    keyboard_init();
    
    display_banner();
    term_write_text("\n\n");
    
    // [KFS-2] Mandatory tests

    term_write_text("[Mandatory Test: GDT and stack Implementation] (see codebase: gdt.c - gdt.asm)\n");
    term_write_text("[Mandatory Test: iso < 10MB (use make size at root)]\n");
    
    // [KFS-2] Bonus tests

    term_write_text("\n");
        
    term_write_text("[Bonus Test: Minimalistic shell] try shell commands: help/panic/stack/reboot\n");
    term_write_text("[Bonus Test: kernel_printf helper] ");
    kernel_printf("d: %d - s: %s - x: %x - X: %X - p: %p", 123, "RNCP", 123, 123, 0);
    term_write_text("\n");

    kernel_shell();

    return (0);
}
