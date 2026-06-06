#include "kernel.h"

void	handle_shell_command(const char *command)
{
	if (!command[0])
		return;
	if (ft_strcmp(command, "help") == 0)
		kernel_printf("Commands: help, stack, panic, reboot\n");
	else if (ft_strcmp(command, "panic") == 0)
		kernel_panic("Halt Kernel...");
	else if (ft_strcmp(command, "stack") == 0)
		print_stack();
	else if (ft_strcmp(command, "reboot") == 0)
		reboot();
	else
		kernel_printf("%s: command not found\n", command);
}

void print_stack(void)
{
    struct frame *frame = (struct frame *)__builtin_frame_address(0);

    for (int i = 0; frame && i < 16; i++) {
        
        if (frame->ret < 0x00100000)
            break;

        kernel_printf("frame %d: ret=0x%x\n", i, frame->ret);

        if (!frame->prev || frame->prev <= frame)
            break;

        frame = frame->prev;
    }
}

void reboot(void)
{
    outb(PS2_IO_COMMAND_REGISTER, CMD_REBOOT);
}

void kernel_panic(const char *msg)
{
    kernel_printf("KERNEL PANIC: %s\n", msg);
    for (int i = 0; msg[i]; i++) {
        outb(0x3F8, msg[i]);
    }
    outb(0x3F8, '\n');
    while (1) {
        __asm__ __volatile__("hlt");
    }
}