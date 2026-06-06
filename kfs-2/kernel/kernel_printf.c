#include "kernel.h"

static void print_uint(ui32_t value)
{
    if (value / 10) {
        print_uint(value / 10);
    }
    term_putchar('0' + (value % 10));
}

static void print_int(i32_t value)
{
    if (value < 0) {
        term_putchar('-');
        value = -value;
    }
    print_uint((ui32_t)value);
}

static void print_hexadecimal(ui32_t value, int uppercase)
{
    const char *digits = uppercase ? "0123456789ABCDEF" : "0123456789abcdef";
    if (value >= 16) {
        print_hexadecimal(value / 16, uppercase);
    }
    term_putchar(digits[value % 16]);
}

static void print_ptr(void *ptr)
{
    term_putchar('0');
    term_putchar('x');
    print_hexadecimal((ui32_t)ptr, 0);
}

static void print_string(const char *string)
{
    while (*string) {
        term_putchar(*string++);
    }
}

int kernel_printf(const char *format, ...)
{
    va_list first_arg;
    va_start(first_arg, format);

    int count = 0;
    while (*format) {
        if (*format != '%') {
            term_putchar(*format++);
            count++;
        } else {
            format++;

            int width = 0;
            while (*format >= '0' && *format <= '9') {
                width = width * 10 + (*format - '0');
                format++;
            }

            if (*format == 'l' || *format == 'h') {
                format++;
            }

            switch (*format) {
                case 'd': {
                    i32_t value = va_arg(first_arg, i32_t);
                    print_int(value);
                    count += (value < 0) ? 11 : 10;
                    break;
                }
                case 'u': {
                    ui32_t value = va_arg(first_arg, ui32_t);
                    print_uint(value);
                    count += 10;
                    break;
                }
                case 'x': {
                    ui32_t value = va_arg(first_arg, ui32_t);
                    print_hexadecimal(value, 0);
                    count += 8;
                    break;
                }
                case 'X': {
                    ui32_t value = va_arg(first_arg, ui32_t);
                    print_hexadecimal(value, 1);
                    count += 8;
                    break;
                }
                case 'p': {
                    void *ptr = va_arg(first_arg, void*);
                    print_ptr(ptr);
                    count += 10;
                    break;
                }
                case 's': {
                    char *string = va_arg(first_arg, char *);
                    print_string(string);
                    while (*string) {
                        count++;
                        string++;
                    }
                    break;
                }
                case 'c': {
                    char c = (i8_t)va_arg(first_arg, i32_t);
                    term_putchar(c);
                    count++;
                    break;
                }
                default: {
                    term_putchar('%');
                    term_putchar(*format);
                    count += 2;
                    break;
                }
            }
            format++;
        }
    }
    va_end(first_arg);
    return count;
}
