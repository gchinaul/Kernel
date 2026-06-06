#include "kernel.h"

static struct gdt_entry gdt[GDT_ENTRIES] __attribute__((section(".gdt")));
struct gdt_ptr   gp;

static void gdt_set_segment(int num, ui32_t base, ui32_t limit, ui8_t access, ui8_t gran)
{
	gdt[num].base_low = GDT_BASE_LOW(base);
	gdt[num].base_middle = GDT_BASE_MIDDLE(base);
	gdt[num].base_high = GDT_BASE_HIGH(base);
	gdt[num].limit_low = GDT_LIMIT_LOW(limit);
	gdt[num].granularity = GDT_LIMIT_HIGH(limit);
	gdt[num].granularity |= GDT_FLAGS(gran);
	gdt[num].access = access;
}

extern void gdt_flush(ui32_t);

void gdt_init(void)
{
	gp.limit = (sizeof(struct gdt_entry) * GDT_ENTRIES) - 1;
	
	gp.base = (ui32_t)&gdt;

	// Params: num (id), base (start addr), limit (size), access (seg type), granularity (seg size)
	gdt_set_segment(0, 0, 0, GDT_NULL, 0x00); 
	gdt_set_segment(1, 0, GDT_LIMIT_4GB, GDT_KERNEL_CODE, GDT_FLAGS_4K_32BIT); 
	gdt_set_segment(2, 0, GDT_LIMIT_4GB, GDT_KERNEL_DATA, GDT_FLAGS_4K_32BIT);
	gdt_set_segment(3, 0, GDT_LIMIT_4GB, GDT_KERNEL_STACK, GDT_FLAGS_4K_32BIT);
	gdt_set_segment(4, 0, GDT_LIMIT_4GB, GDT_USER_CODE, GDT_FLAGS_4K_32BIT);
	gdt_set_segment(5, 0, GDT_LIMIT_4GB, GDT_USER_DATA, GDT_FLAGS_4K_32BIT);
	gdt_set_segment(6, 0, GDT_LIMIT_4GB, GDT_USER_STACK, GDT_FLAGS_4K_32BIT);

	gdt_flush((ui32_t)&gp);
}
