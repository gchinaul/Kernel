#include "kernel.h"

extern ui16_t	*term_buffer;

static ui8_t	*term_get_row(size_t row)
{
	return (term_get_current_buffer() + row * ROW_BYTES);
}

static void	term_copy_bytes(ui8_t *dst, const ui8_t *src, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		dst[i] = src[i];
		i++;
	}
}

static void	term_copy_row(size_t dst_row, size_t src_row)
{
	term_copy_bytes(term_get_row(dst_row), term_get_row(src_row), ROW_BYTES);
}

static void	term_save_row(ui8_t dst[ROW_BYTES], size_t row)
{
	term_copy_bytes(dst, term_get_row(row), ROW_BYTES);
}

static void	term_restore_row(size_t row, const ui8_t src[ROW_BYTES])
{
	term_copy_bytes(term_get_row(row), src, ROW_BYTES);
}

static void	term_shift_rows_up(void)
{
	size_t	y = 1;
	while (y < VGA_HEIGHT)
	{
		term_copy_row(y - 1, y);
		y++;
	}
}

static void	term_clear_row(size_t row)
{
	ui8_t	*dst;
	size_t	x;

	dst = term_get_row(row);
	x = 0;
	while (x < VGA_WIDTH)
	{
		dst[x * 2] = ' ';
		dst[x * 2 + 1] = term.color;
		x++;
	}
}

static void	term_push_history_row(
	ui8_t history[SCROLL_HISTORY_MAX][ROW_BYTES],
	int *count, size_t row)
{
	int	i;

	if (*count == SCROLL_HISTORY_MAX)
	{
		i = 1;
		while (i < SCROLL_HISTORY_MAX)
		{
			term_copy_bytes(history[i - 1], history[i], ROW_BYTES);
			i++;
		}
		*count = SCROLL_HISTORY_MAX - 1;
	}

	term_save_row(history[*count], row);
	(*count)++;
}

void	scroll_down(void)
{
	scroller_t	*s = term_get_scroller();

	term_push_history_row(s->back, &s->back_count, 0);
	s->forward_count = 0;
	term_shift_rows_up();
	term_clear_row(VGA_HEIGHT - 1);
	term_render_current_screen();
	term.row = VGA_HEIGHT - 1;
	term.column = 0;
	update_cursor(term.column, term.row);
}

void	scroll_view_down(void)
{
	scroller_t	*s = term_get_scroller();

	if (s->forward_count == 0)
		return;

	term_push_history_row(s->back, &s->back_count, 0);
	term_shift_rows_up();
	s->forward_count--;
	term_restore_row(VGA_HEIGHT - 1, s->forward[s->forward_count]);
	term_render_current_screen();
	update_cursor(term.column, term.row);
}
