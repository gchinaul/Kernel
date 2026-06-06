#pragma once
#ifndef KERNEL_SHELL_H
# define KERNEL_SHELL_H

# define PS2_IO_DATA_PORT 0x60
# define PS2_IO_STATUS_REGISTER 0x64
# define PS2_IO_COMMAND_REGISTER 0x64

# define SHELL_PROMPT "kernel$> "
# define MAX_INPUT_LENGTH 4096

struct frame {
    struct frame *prev;
    ui32_t ret;
};

typedef struct shell_context
{
    char input[MAX_INPUT_LENGTH + 1];
    size_t length;
    bool prompt_pending;
} shell_context_t;

void    kernel_shell_init_contexts(void);
void    kernel_shell(void);
shell_context_t	*kernel_shell_get_context(void);
void    kernel_shell_clear_input(shell_context_t *context);
void    kernel_shell_restore_prompt(void);
void    kernel_shell_handle_char(shell_context_t *context, i8_t c);
void    kernel_shell_handle_enter(shell_context_t *context);
void    kernel_shell_handle_backspace(shell_context_t *context);
void    kernel_shell_handle_printable(shell_context_t *context, i8_t c);

#endif