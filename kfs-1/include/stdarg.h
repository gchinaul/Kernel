#pragma once

#ifndef STDARG_H
#define STDARG_H

#include "type.h"

#if defined(__i386__) || defined(_M_IX86)
    #define ARCH_X86 1
#else
    #error "This is NOT supposed to happen."
#endif

#if defined(ARCH_X86)
    typedef char *va_list;

    #define ALIGN(ptr, align) (((unsigned long)(ptr) + (align) - 1) & ~((align) - 1))
        #define ALIGNOF(type) \
        (sizeof(type) == 1 ? 1 : \
        sizeof(type) == 2 ? 2 : \
        sizeof(type) == 4 ? 4 : \
        sizeof(type) == 8 ? 8 : 4)

    #define va_start(ap, fmt) (ap = (char *)&fmt + sizeof(fmt))
    
    #define va_arg(ap, type) \
        (*(type *)((ap = (char *)ALIGN(ap, ALIGNOF(type))), ap += sizeof(type), ap - sizeof(type)))
    
    #define va_end(ap) ((void)0)
#endif

#endif