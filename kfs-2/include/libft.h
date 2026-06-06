#pragma once
#ifndef LIBFT_H
#define LIBFT_H


static inline int ft_strlen(const char *s)
{
    int i = 0;

    while (s[i] != '\0')
        i++;
    return (i);
}

static inline void ft_itoa(i32_t num, char *str, ui32_t base)
{
    const char *digits = "0123456789abcdef";
    size_t i = 0;
    ui32_t is_negative = 0;

    if (num < 0 && base == 10) {
        is_negative = 1;
        num = -num;
    }

    if (num == 0) {
        str[i++] = '0';
    } else {
        while (num > 0) {
            str[i++] = digits[num % base];
            num /= base;
        }
    }

    if (is_negative) {
        str[i++] = '-';
    }

    str[i] = '\0';

    for (size_t j = 0; j < i / 2; j++) {
        char temp = str[j];
        str[j] = str[i - j - 1];
        str[i - j - 1] = temp;
    }
}

static inline int ft_strcmp(const char *s1, const char *s2)
{
    while (*s1 && (*s1 == *s2))
    {
        s1++;
        s2++;
    }
    return (*(ui8_t *)s1 - *(ui8_t *)s2);
}

static inline void    *kmemset(void *dst, int c, size_t n)
{
    ui8_t     *p;

    p = (ui8_t *)dst;
    while (n--)
        *p++ = (ui8_t)c;
    return (dst);
}

#endif