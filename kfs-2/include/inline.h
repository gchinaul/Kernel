#pragma once
#ifndef INLINE_H
#define INLINE_H

#include "kernel.h"

/* VGA inline section */

static inline ui8_t vga_entry_color(enum vga_color fg, enum vga_color bg) 
{
	return fg | bg << 4;
}

static inline ui16_t vga_entry(unsigned char uc, ui8_t color) 
{
	return (ui16_t) uc | (ui16_t) color << 8;
}

/* CURSOR inline section */

static inline void outb(unsigned short port, unsigned char val)
{
    __asm__ volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}

static inline unsigned char inb(unsigned short port)
{
    unsigned char ret;
    __asm__ volatile ("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

static inline void enable_cursor(ui8_t cursor_start, ui8_t cursor_end)
{
	outb(0x3D4, 0x0A);
	outb(0x3D5, (inb(0x3D5) & 0xC0) | cursor_start);

	outb(0x3D4, 0x0B);
	outb(0x3D5, (inb(0x3D5) & 0xE0) | cursor_end);
}

static inline void update_cursor(int x, int y)
{
	ui16_t pos = y * VGA_WIDTH + x;

	outb(0x3D4, 0x0F);
	outb(0x3D5, (ui8_t) (pos & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (ui8_t) ((pos >> 8) & 0xFF));
}

#endif