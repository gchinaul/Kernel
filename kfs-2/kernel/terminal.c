 #include "ksh.h"
 #include "vga.h"
 #include "terminal.h"
 #include "cursor.h"
 #include "libft.h"

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer = (uint16_t*)VGA_MEMORY;

void terminal_init()
{
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
}

static void terminal_scroll()
{
	for (size_t y = 1; y < VGA_HEIGHT; y++) {
		
			for (size_t x = 0; x < VGA_WIDTH; x++) {
					terminal_buffer[(y - 1) * VGA_WIDTH + x] = terminal_buffer[y * VGA_WIDTH + x];
			}
	}

	for (size_t x = 0; x < VGA_WIDTH; x++) {
			terminal_buffer[(VGA_HEIGHT - 1) * VGA_WIDTH + x] = vga_entry(' ', terminal_color);
	}

	terminal_row = VGA_HEIGHT - 1;
	terminal_column = 0;

	update_cursor(terminal_column, terminal_row);
}

/**
 * @note This function doesn't update the cursor
 */
void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) 
{
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
}

void terminal_putchar(char c)
{
	if (c == '\n') {
		terminal_column = 0;
		if (++terminal_row == VGA_HEIGHT)
			terminal_scroll();
		update_cursor(terminal_column, terminal_row);
		return ;
	}
	
	terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
	
	if (++terminal_column == VGA_WIDTH) {
		terminal_column = 0;
		if (++terminal_row == VGA_HEIGHT)
			terminal_scroll();
	}

	update_cursor(terminal_column, terminal_row);
}

void terminal_color_putchar(char c, uint8_t color)
{
	terminal_putentryat(c, color, terminal_column, terminal_row);
	
	if (++terminal_column == VGA_WIDTH) {
		terminal_column = 0;
		if (++terminal_row == VGA_HEIGHT)
			terminal_scroll();
	}
}

void terminal_putchar_line(const char* string)
{
	int size = strlen(string);

	for(int i = 0; i < size; i++)
	{
		terminal_putchar(string[i]);
	}
}