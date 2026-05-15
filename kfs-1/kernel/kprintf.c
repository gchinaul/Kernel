#include "ksh.h"
#include "terminal.h"

static void kvprintf(const char *fmt, va_list ap, t_emit emit, void *ctx)
{
	char	*s;

	while (*fmt) {
		if (*fmt == KESC && *(fmt + 1) == '[') {
			fmt += 2;
			if (*fmt == 'r') {
				terminal_color = vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
				fmt++;
			} else {
				uint8_t fg = 0;
				uint8_t bg = (terminal_color >> 4) & 0xF;

				while (*fmt >= '0' && *fmt <= '9')
					fg = fg * 10 + (*fmt++ - '0');
				if (*fmt == ';') {
					fmt++;
					bg = 0;
					while (*fmt >= '0' && *fmt <= '9')
						bg = bg * 10 + (*fmt++ - '0');
				}
				terminal_color = vga_entry_color(fg, bg);
				if (*fmt == ']')
					fmt++;
			}
			continue;
		}
		if (*fmt != '%') {
			emit(*fmt++, ctx);
			continue;
		}
		fmt++;
		switch (*fmt) {
			case 'c': emit((char)va_arg(ap, int), ctx);
				break;
			case 's':
				s = va_arg(ap, char *);
				if (!s)
					s = "(null)";
				while (*s)
					emit(*s++, ctx);
				break;
			case '%':
				emit('%', ctx);
				break;
		}
		fmt++;
	}
}

static void emit_vga(char c, void *ctx)
{
	(void)ctx;
	terminal_putchar(c);
}

void kprintf(const char *fmt, ...)
{
	va_list	ap;
	va_start(ap, fmt);
	kvprintf(fmt, ap, emit_vga, NULL);
	va_end(ap);
}