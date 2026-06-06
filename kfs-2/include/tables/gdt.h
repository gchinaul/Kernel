#pragma once
#ifndef GDT_H
# define GDT_H

# include "type.h"

// GDT constants
# define GDT_ENTRIES 7
# define GDT_LIMIT_4GB 0xFFFFF
# define GDT_FLAGS_4K_32BIT 0xCF

// GDT access byte flags
# define GDT_NULL 0x00
# define GDT_KERNEL_CODE 0x9A
# define GDT_KERNEL_DATA 0x92
# define GDT_KERNEL_STACK 0x92
# define GDT_USER_CODE 0xFA
# define GDT_USER_DATA 0xF2
# define GDT_USER_STACK 0xF2

// Macros to extract base and limit parts for GDT entries
# define GDT_BASE_LOW(base)		((base & 0xFFFF)) // lower 16 bits
# define GDT_BASE_MIDDLE(base)	((base >> 16) & 0xFF) // middle 8 bits
# define GDT_BASE_HIGH(base)	((base >> 24) & 0xFF) // upper 8 bits
# define GDT_LIMIT_LOW(limit)	((limit & 0xFFFF)) // lower 16 bits
# define GDT_LIMIT_HIGH(limit)	((limit >> 16) & 0x0F) // upper 4 bits
# define GDT_FLAGS(gran)		((gran) & 0xF0) // upper 4 bits

struct gdt_entry
{
	ui16_t	limit_low;
	ui16_t	base_low;
	ui8_t	base_middle;
	ui8_t	access;
	ui8_t	granularity;
	ui8_t	base_high;
} __attribute__((packed));

struct gdt_ptr
{
	ui16_t	limit;
	ui32_t	base;
} __attribute__((packed));

void gdt_init(void);

#endif
