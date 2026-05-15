#include "ksh.h"

struct frame {
    struct frame *prev;
    uint32_t ret;
};

void stack_trace(void)
{
    struct frame *f = (struct frame *)__builtin_frame_address(0);
    int i = 0;

    while (f && i < 16) {
        if (f->ret < 0x00100000)
            break;
        kprintf("frame %d: ret=0x%x\n", i, f->ret);
        if (!f->prev || f->prev <= f) break;
        f = f->prev;
        i++;
    }
}
