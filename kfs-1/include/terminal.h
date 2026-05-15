#ifndef TERMINAL_H
# define TERMINAL_H

void terminal_init();
void terminal_color_putchar(char c, uint8_t color);
void terminal_putchar(char c);
void terminal_putchar_line(const char* string);
void terminal_putentryat(char c, uint8_t color, size_t x, size_t y);

extern uint8_t	terminal_color;

#endif