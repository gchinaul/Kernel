#pragma once
#ifndef TYPE_H
# define TYPE_H

typedef unsigned char           uint8_t;
typedef unsigned short          uint16_t;
typedef unsigned int            uint32_t;
typedef unsigned long long      uint64_t;

typedef signed char             int8_t;
typedef signed short            int16_t;
typedef signed int              int32_t;
typedef signed long long        int64_t;

typedef unsigned int            size_t;

typedef uint8_t                 bool;
# define TRUE                   1
# define FALSE                  0

# ifndef NULL
#   define NULL                 ((void *)0)
# endif

# define VGA_MEMORY 0xB8000
# define VGA_WIDTH 80
# define VGA_HEIGHT 25

#endif