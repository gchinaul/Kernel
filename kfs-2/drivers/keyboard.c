#include "kernel.h"

extern term_t term;

keyboard_state_t ks = {0};

/* Scancode maps. Ordered as standard QWERTY layout. Special keys handled separately (CAPS, SHIFT) */

static const char   g_scancode_map[128] =
{
    [0x00] = 0, [0x01] = ESC,

	// First row
	[0x29] = '`',
	[0x02] = '1', [0x03] = '2', [0x04] = '3', [0x05] = '4', [0x06] = '5', [0x07] = '6', [0x08] = '7', [0x09] = '8', [0x0A] = '9', [0x0B] = '0',
	[0x0C] = '-', [0x0D] = '=', [0x0E] = BACKSPACE, 
	// Second row
	[0x0F] = TAB,
	[0x10] = 'q', [0x11] = 'w', [0x12] = 'e', [0x13] = 'r', [0x14] = 't', [0x15] = 'y', [0x16] = 'u', [0x17] = 'i', [0x18] = 'o', [0x19] = 'p',
	[0x1A] = '[', [0x1B] = ']', [0x2B] = '\\',
	// Third row
	[0x1E] = 'a', [0x1F] = 's', [0x20] = 'd', [0x21] = 'f', [0x22] = 'g', [0x23] = 'h', [0x24] = 'j', [0x25] = 'k', [0x26] = 'l',
	[0x27] = ';', [0x28] = '\'', [0x1C] = ENTER,
	// Fourth row
	[0x2C] = 'z', [0x2D] = 'x', [0x2E] = 'c', [0x2F] = 'v', [0x30] = 'b', [0x31] = 'n', [0x32] = 'm',
	[0x33] = ',', [0x34] = '.', [0x35] = '/',
	// Fifth row
	[0x39] = ' ',

};

static const char   g_scancode_shift[128] =
{
    [0x00] = 0, [0x01] = ESC,
	// First row
	[0x29] = '~',
	[0x02] = '!', [0x03] = '@', [0x04] = '#', [0x05] = '$', [0x06] = '%', [0x07] = '^', [0x08] = '&', [0x09] = '*', [0x0A] = '(', [0x0B] = ')',
	[0x0C] = '_', [0x0D] = '+', [0x0E] = BACKSPACE, 
	// Second row
	[0x0F] = TAB,
	[0x10] = 'Q', [0x11] = 'W', [0x12] = 'E', [0x13] = 'R', [0x14] = 'T', [0x15] = 'Y', [0x16] = 'U', [0x17] = 'I', [0x18] = 'O', [0x19] = 'P',
	[0x1A] = '{', [0x1B] = '}', [0x2B] = '|',
	// Third row
	[0x1E] = 'A', [0x1F] = 'S', [0x20] = 'D', [0x21] = 'F', [0x22] = 'G', [0x23] = 'H', [0x24] = 'J', [0x25] = 'K', [0x26] = 'L',
	[0x27] = ':', [0x28] = '"', [0x1C] = ENTER,
	// Fourth row
	[0x2C] = 'Z', [0x2D] = 'X', [0x2E] = 'C', [0x2F] = 'V', [0x30] = 'B', [0x31] = 'N', [0x32] = 'M',
	[0x33] = '<', [0x34] = '>', [0x35] = '?',
	// Fifth row
	[0x39] = ' ',
};

void keyboard_init(void)
{
	(void)inb(PS2_IO_DATA_PORT);
}

bool keyboard_poll(void)
{
	if ((inb(PS2_IO_STATUS_REGISTER) & 0x01) == 0)
		return (FALSE);
	keyboard_handle_scancode();
	return (TRUE);
}

void keyboard_handle_scancode(void)
{
	ui8_t		scancode;

	scancode = inb(PS2_IO_DATA_PORT);

	keyboard_set_flags(scancode);

	if (ks.kb_flags & LALT_FLAG)
	{
		ui8_t screen_index;
		if (is_screen_switching_key(scancode, &screen_index)) {
			term_switch_screen(screen_index);
			return;
		}
	}

	if (scancode >= 128)
		return;

	ks.kb_queue[0] = keyboard_getchar(scancode);
	return;
}

void keyboard_set_flags(ui8_t scancode)
{

	if (scancode == KB_LALT)
	{
		ks.kb_flags |= LALT_FLAG;
		return;
	}

	if (scancode == (KB_LALT | KB_RELEASE_MASK))
	{
		ks.kb_flags &= ~LALT_FLAG;
		return;
	}

	if (scancode & KB_RELEASE_MASK)
	{
		scancode &= ~KB_RELEASE_MASK;
		if (scancode == KB_LSHIFT || scancode == KB_RSHIFT)
			ks.kb_flags &= ~SHIFT_FLAG;
		return;
	}

	if (scancode == KB_CAPSLOCK)
	{
		ks.kb_flags ^= CAPS_FLAG;
		return;
	}

	if (scancode == KB_LSHIFT || scancode == KB_RSHIFT)
		ks.kb_flags |= SHIFT_FLAG;
}

ui8_t screen_switching_keys[] = {KB_F1, KB_F2, KB_F3, KB_F4};

bool is_screen_switching_key(ui8_t scancode, ui8_t *screen_index) {
    for (size_t i = 0; i < sizeof(screen_switching_keys); i++) {
        if (scancode == screen_switching_keys[i]) {
			*screen_index = i;
			return (TRUE);
        }
    }
	return (FALSE);
}

char keyboard_getchar(ui8_t scancode) {

	char c = (ks.kb_flags & (SHIFT_FLAG | CAPS_FLAG)) ? g_scancode_shift[scancode] : g_scancode_map[scancode];
	return (c);
}
