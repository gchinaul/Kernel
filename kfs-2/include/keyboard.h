#pragma once

#ifndef KEYBOARD_H
# define KEYBOARD_H

# include "type.h"

# define KB_DATA_PORT 0x60
# define KB_STATUS_PORT

# define KB_BACKSCPACE		0x0E
# define KB_ENTER			0x1C
# define KB_LSHIFT			0x2A
# define KB_RSHIFT			0x36
# define KB_CAPS			0x3A
# define KB_RELEASE_MASK	0x80

void	keyboard_init(void);
char	keyboard_getchar(void);
void 	keyboard_handler(void);

#endif