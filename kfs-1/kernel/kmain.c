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

    __asm__ volatile("cli");

    // Init drivers
    term_init();
    keyboard_init();
    
    display_banner();
    term_write_text("\n\n");
    
    // [KFS-1] Mandatory tests

    term_write_text("[Mandatory Test: GRUB on virtual image, ASM multiboot] (see codebase)\n");
    term_write_text("[Mandatory Test: iso < 10MB (use make size at root)]\n");
    term_write_text("[Mandatory Test: Display 42 on the screen] ");
    term_write_text("42");
    
    // [KFS-1] Bonus tests

    term_write_text("\n");
        
    term_write_text("[Bonus Test: Color support] ");
    term_color_putchar('4', vga_entry_color(VGA_COLOR_GREEN , VGA_COLOR_BLACK));
    term_color_putchar('2', vga_entry_color(VGA_COLOR_GREEN, VGA_COLOR_BLACK));
    term_color_putchar('N', vga_entry_color(VGA_COLOR_BLUE, VGA_COLOR_LIGHT_BLUE));
    term_color_putchar('I', vga_entry_color(VGA_COLOR_CYAN, VGA_COLOR_LIGHT_CYAN));
    term_color_putchar('C', vga_entry_color(VGA_COLOR_MAGENTA, VGA_COLOR_LIGHT_MAGENTA));
    term_color_putchar('E', vga_entry_color(VGA_COLOR_BROWN, VGA_COLOR_LIGHT_BROWN));
    term_write_text("\n");

    term_write_text("[Bonus Test: kernel_printf helper] ");
    kernel_printf("d: %d - s: %s - x: %x - X: %X - p: %p", 123, "RNCP", 123, 123, 0);
    term_write_text("\n");
    
    term_write_text("[Bonus Test: Keyboard input handling (type to display characters in the shell)]\n");
    term_write_text("[Bonus Test: Terminal scrolling and cursor support (type to fill the screen)]\n");
    term_write_text("[Bonus Test: Screens switching and shortcuts (switch screens with F1-F4)]\n");
    term_write_text("\n");

    kernel_shell();

    return (0);
}
