#include "ksh.h"
#include "libft.h"
#include "io.h"

extern void irq1_stub(void);
struct idt_entry	idt[256];

void idt_set_gate(int n, uint32_t handler)
{
	idt[n].offset_low = handler & 0xFFFF;
	idt[n].selector = 0x08;
	idt[n].zero = 0;
	idt[n].type_attr = 0x8E;
	idt[n].offset_high = (handler >> 16) & 0xFFFF;
}

void idt_load(struct idt_ptr *idtp)
{
	__asm__ volatile("lidt (%0)" : : "r"(idtp));
}

void pic_remap(void)
{
	outb(0x20, 0x11);
	outb(0xA0, 0x11);

	outb(0x21, 0x20);
	outb(0xA1, 0x28);

	outb(0x21, 0x04);
	outb(0xA1, 0x02);

	outb(0x21, 0x01);
	outb(0xA1, 0x01);

	outb(0x21, 0xFD);
	outb(0xA1, 0xFF);
}

struct idt_ptr idtp;

void idt_init(void)
{
	kmemset(idt, 0, sizeof(idt));
	pic_remap();
	idt_set_gate(33, (uint32_t)irq1_stub);
	idtp.limit = sizeof(idt) - 1;
	idtp.base = (uint32_t)&idt;
	idt_load(&idtp);
}

