#pragma once
#ifndef KERNEL_SHELL_CMDS_H
# define KERNEL_SHELL_CMDS_H

# define CMD_REBOOT 0xFE

void handle_shell_command(const char *command);
void print_stack(void);
void reboot(void);
void kernel_panic(const char *msg);

#endif