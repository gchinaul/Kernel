#include "ksh.h"
#include "io.h"
#include "terminal.h"
#include "cursor.h"

/* https://users.utcluj.ro/~baruch/sie/labor/PS2/Scan_Codes_Set_1.htm */

static const char   g_scancode_map[128] =
{
    0,   27,  '1', '2', '3', '4', '5', '6', '7', '8', /* 0x00 - 0x09 */
    '9', '0', '-', '=', '\b', '\t',                    /* 0x0A - 0x0F */
    'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', /* 0x10 - 0x19 */
    '[', ']', '\n', 0,                                  /* 0x1A - 0x1D */
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', /* 0x1E - 0x27 */
    '\'', '`', 0,  '\\',                               /* 0x28 - 0x2B */
    'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', /* 0x2C - 0x35 */
    0,   '*', 0,   ' ',                                 /* 0x36 - 0x39 */
};

static const char   g_scancode_shift[128] =
{
    0,   27,  '!', '@', '#', '$', '%', '^', '&', '*',
    '(', ')', '_', '+', '\b', '\t',
    'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',
    '{', '}', '\n', 0,
    'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':',
    '"', '~', 0,   '|',
    'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?',
    0,   '*', 0,   ' ',
};

static int 	g_shift = 0;
static int  g_caps  = 0;

/* nothing to configure for PS/2 stock */
void keyboard_init(void)
{
	(void)inb(KB_DATA_PORT);
}

/* read scan code and return the ascii or O */
char keyboard_getchar(void)
{
	uint8_t		scode;
	char        c;

	scode = inb(KB_DATA_PORT);
	if (scode & KB_RELEASE_MASK)
	{
		scode &= ~KB_RELEASE_MASK;
		if (scode == KB_LSHIFT || scode == KB_RSHIFT)
			g_shift = 0;
		return (0);
	}
	if (scode == KB_LSHIFT || scode == KB_RSHIFT)
	{
		g_shift = 1;
		return (0);
	}
	if (scode == KB_CAPS)
	{
		g_caps ^= 1;
		return (0);
	}
	if (scode >= 128)
		return (0);

	c = (g_shift || g_caps) ? g_scancode_shift[scode] : g_scancode_map[scode];
	return (c);
}

extern size_t terminal_row;
extern size_t terminal_column;

void keyboard_handler(void)
{
	uint8_t	scode = inb(0x60);
	
	if (scode & 0x80)
		return ;
	if (scode >= 128)
		return ;

	char c = g_scancode_map[scode];

	if (c == '\b')
	{
		if (terminal_column > 0)
		{
			terminal_column--;
			terminal_putentryat(' ', terminal_color, terminal_column, terminal_row);
			update_cursor(terminal_column, terminal_row);
		}
	}
	else if (c == '\n')
	{
		terminal_putchar('\n');
	}
	else if (c)
	{
		terminal_putchar(c);
	}
}
