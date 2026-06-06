#pragma once
#ifndef SCROLLER_H
# define SCROLLER_H

# include "type.h"
# include "term.h"

# define SCROLL_HISTORY_MAX (VGA_HEIGHT * 100)
# define ROW_BYTES          (VGA_WIDTH * 2)

typedef struct scroller_t
{
	ui8_t	back[SCROLL_HISTORY_MAX][ROW_BYTES];
	int		back_count;
	ui8_t	forward[SCROLL_HISTORY_MAX][ROW_BYTES];
	int		forward_count;
}	scroller_t;

void	scroll_down(void);
void	scroll_view_down(void);

#endif