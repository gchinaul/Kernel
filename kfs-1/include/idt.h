#pragma once

#ifndef IDT_H
# define IDT_H

#include "type.h"

struct idt_entry {
	uint16_t	offset_low;
	uint16_t	selector;
	uint8_t		zero;
	uint8_t		type_attr;
	uint16_t	offset_high;
};

struct idt_ptr
{
	uint16_t	limit;
	uint32_t	base;
} __attribute__((packed));

void idt_set_gate(int n, uint32_t handler);
void idt_load(struct idt_ptr *idtp);
void idt_init(void);
void pic_remap(void);


#endif