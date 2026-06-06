#pragma once
#ifndef TYPE_H
# define TYPE_H

typedef unsigned char           ui8_t;
typedef unsigned short          ui16_t;
typedef unsigned int            ui32_t;
typedef unsigned long long      ui64_t;

typedef signed char             i8_t;
typedef signed short            i16_t;
typedef signed int              i32_t;
typedef signed long long        i64_t;

typedef unsigned int            size_t;

typedef ui8_t                 bool;
# define TRUE                   1
# define FALSE                  0

# ifndef NULL
#   define NULL                 ((void *)0) 
# endif

#endif