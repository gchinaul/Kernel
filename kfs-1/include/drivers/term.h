#pragma once
#ifndef TERM_H
# define TERM_H

# include "type.h"
# include "scroller.h"

# define VGA_WIDTH 80
# define VGA_HEIGHT 25
# define SCREEN_SIZE (VGA_WIDTH * VGA_HEIGHT * 2)
# define NB_SCREENS 4
# define TAB_LENGTH 4

extern ui8_t current_screen;

typedef struct cursor_t
{
	size_t	old_x;
	size_t	old_y;
	size_t	cur_x;
	size_t	cur_y;
}	cursor_t;

typedef struct screen_t
{
	ui8_t		id;
	ui8_t		buffer[SCREEN_SIZE];
	cursor_t	cursor;
	scroller_t	scroller;
}	screen_t;

typedef struct term_t
{
	screen_t	*screen;
	screen_t	screens[NB_SCREENS];
	size_t	column;
	size_t	row;
	ui8_t	color;
}	term_t;

extern term_t	term;

void	term_init(void);
void	term_focus_on_prompt(void);
void	term_putentryat(char c, ui8_t color, size_t x, size_t y);
void	term_putchar(char c);
void	term_color_putchar(char c, ui8_t color);
void	term_putchar_line(const char *string);
void	term_write(const char *data, size_t size);
void	term_write_text(const char *data);
void	term_save_current_screen(void);
void	term_switch_screen(ui8_t id_new_screen);
void	term_copy_cell(size_t dst, size_t src);
void	term_render_current_screen(void);

scroller_t	*term_get_scroller(void);
ui8_t		*term_get_current_buffer(void);
ui8_t		*term_get_screen_buffer(ui8_t id);

#endif
