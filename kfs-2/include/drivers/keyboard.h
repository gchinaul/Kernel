#pragma once
#ifndef KEYBOARD_H
# define KEYBOARD_H

# include "type.h"

// Keyboard responses
# define ACK                0xFA
# define RESEND              0xFE

// Special keys
# define ESC             27
# define BACKSPACE       '\b'
# define ENTER           '\n'
# define TAB             '\t'
# define CARRIAGE_RET    '\r'

// Scancode map
# define KB_LSHIFT			0x2A
# define KB_RSHIFT			0x36
# define KB_CAPSLOCK		0x3A
# define KB_RELEASE_MASK	0x80

// Screen switching keys
# define KB_LALT            0x38
# define KB_F1              0x3B
# define KB_F2              0x3C
# define KB_F3              0x3D
# define KB_F4              0x3E

// Flags
# define CAPS_FLAG          (1 << 0)
# define SHIFT_FLAG         (1 << 1)
# define RELEASE_FLAG       (1 << 2)
# define LALT_FLAG          (1 << 3)

// Misc settings
# define TAB_LENGTH       4


typedef struct keyboard_state
{
    ui8_t kb_flags;
    char kb_queue[256];
} keyboard_state_t;

void	keyboard_init(void);
bool	keyboard_poll(void);
void    keyboard_handle_scancode(void);
void    keyboard_set_flags(ui8_t scancode);
bool    is_screen_switching_key(ui8_t scancode, ui8_t *screen_index);
char	keyboard_getchar(ui8_t scancode);

#endif