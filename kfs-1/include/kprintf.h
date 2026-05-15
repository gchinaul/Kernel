#pragma once

#include "vga.h"
#include "type.h"

#ifndef KPRINTF_H
# define KPRINTF_H

typedef __builtin_va_list	va_list;

# define va_start(v, l)    __builtin_va_start(v, l)
# define va_arg(v, l)      __builtin_va_arg(v, l)
# define va_end(v)         __builtin_va_end(v)

/* design pattern (strategy pattern) */
typedef void (*t_emit)(char c, void *ctx);

void kprintf(const char *fmt, ...);

#endif
