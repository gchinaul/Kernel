#include "kernel.h"

term_t	term;
ui16_t	*term_buffer = (ui16_t *)VGA_MEMORY;
ui8_t	current_screen = 0;
ui8_t	term_color;

scroller_t	*term_get_scroller(void)
{
	return (&term.screen->scroller);
}

ui8_t	*term_get_current_buffer(void)
{
	return (term.screen->buffer);
}

ui8_t	*term_get_screen_buffer(ui8_t id)
{
	if (id >= NB_SCREENS)
		return (NULL);
	return (term.screens[id].buffer);
}

void	term_render_current_screen(void)
{
	ui8_t	*buf = term_get_current_buffer();
	size_t	i;
	ui8_t	c;
	ui8_t	color;

	i = 0;
	while (i < VGA_WIDTH * VGA_HEIGHT)
	{
		c = buf[i * 2];
		color = buf[i * 2 + 1];
		term_buffer[i] = vga_entry(c, color);
		i++;
	}
}

void	term_focus_on_prompt(void)
{
	scroller_t	*s = term_get_scroller();

	while (s->forward_count > 0)
		scroll_view_down();

	update_cursor(term.column, term.row);
}

void	term_init(void)
{
	ui8_t	i;
	size_t	j;

	term_buffer = (ui16_t *)VGA_MEMORY;
	term.color = vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
	term.column = 0;
	term.row = 0;

	i = 0;
	while (i < NB_SCREENS)
	{
		term.screens[i].id = i;
		kmemset(&term.screens[i].cursor, 0, sizeof(cursor_t));
		kmemset(&term.screens[i].scroller, 0, sizeof(scroller_t));

		j = 0;
		while (j < VGA_WIDTH * VGA_HEIGHT)
		{
			term.screens[i].buffer[j * 2] = ' ';
			term.screens[i].buffer[j * 2 + 1] = term.color;
			j++;
		}
		i++;
	}

	current_screen = 0;
	term.screen = &term.screens[current_screen];

	term_render_current_screen();
	update_cursor(term.column, term.row);
}

void	term_copy_cell(size_t dst, size_t src)
{
	ui8_t	*buf = term_get_current_buffer();
	ui8_t	c = buf[src * 2];
	ui8_t	color = buf[src * 2 + 1];

	buf[dst * 2] = c;
	buf[dst * 2 + 1] = color;
	term_buffer[dst] = vga_entry(c, color);
}

void	term_write_cell(size_t index, ui8_t c, ui8_t color)
{
	ui8_t	*buf = term_get_current_buffer();

	buf[index * 2] = c;
	buf[index * 2 + 1] = color;
	term_buffer[index] = vga_entry(c, color);
}

void	term_putentryat(char c, ui8_t color, size_t x, size_t y)
{
	size_t	index;

	if (x >= VGA_WIDTH || y >= VGA_HEIGHT)
		return;

	index = y * VGA_WIDTH + x;
	term_write_cell(index, c, color);
}

void	term_putchar(char c)
{
	term_focus_on_prompt();

	if (c == BACKSPACE)
	{
		if (term.column > 0)
			term.column--;
		else if (term.row > 0)
		{
			term.row--;
			term.column = VGA_WIDTH - 1;
		}
		else
			return;

		term_putentryat(' ', term.color, term.column, term.row);
		update_cursor(term.column, term.row);
		return;
	}

	if (c == TAB)
	{
		for (size_t i = 0; i < TAB_LENGTH; i++)
			term_putchar(' ');
		return;
	}

	if (c == ENTER || c == CARRIAGE_RET)
	{
		term.column = 0;
		term.row++;
		if (term.row == VGA_HEIGHT)
			scroll_down();
		update_cursor(term.column, term.row);
		return;
	}

	term_putentryat(c, term.color, term.column, term.row);

	term.column++;
	if (term.column == VGA_WIDTH)
	{
		term.column = 0;
		term.row++;
		if (term.row == VGA_HEIGHT)
			scroll_down();
	}

	update_cursor(term.column, term.row);
}

void	term_color_putchar(char c, ui8_t color)
{
	term_focus_on_prompt();

	term_putentryat(c, color, term.column, term.row);

	term.column++;
	if (term.column == VGA_WIDTH)
	{
		term.column = 0;
		term.row++;
		if (term.row == VGA_HEIGHT)
			scroll_down();
	}

	update_cursor(term.column, term.row);
}

void	term_putchar_line(const char *string)
{
	int	i;
	int	size;

	size = ft_strlen(string);
	i = 0;
	while (i < size)
	{
		term_putchar(string[i]);
		i++;
	}
}

void	term_write(const char *data, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		term_putchar(data[i]);
		i++;
	}
}

void	term_write_text(const char *data)
{
	term_write(data, ft_strlen(data));
}

void	term_save_current_screen(void)
{
	term.screen->cursor.cur_x = term.column;
	term.screen->cursor.cur_y = term.row;
}

void	term_switch_screen(ui8_t id_new_screen)
{
	if (id_new_screen >= NB_SCREENS)
		return;

	if (id_new_screen == current_screen)
		return;

	term_save_current_screen();

	current_screen = id_new_screen;
	term.screen = &term.screens[current_screen];

	term.column = term.screen->cursor.cur_x;
	term.row = term.screen->cursor.cur_y;

	term_render_current_screen();
	term_focus_on_prompt();
}
