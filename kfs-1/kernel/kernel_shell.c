#include "kernel.h"

extern term_t				term;
extern keyboard_state_t		ks;
extern ui8_t				current_screen;
static shell_context_t		shell_contexts[NB_SCREENS];

void	kernel_shell_init_contexts(void)
{
	size_t	i;

	i = 0;
	while (i < NB_SCREENS)
	{
		shell_contexts[i].prompt_pending = TRUE;
		shell_contexts[i].length = 0;
		shell_contexts[i].input[0] = '\0';
		i++;
	}
}

void	kernel_shell(void)
{
	ui8_t			active_screen;
	shell_context_t	*context;
	i8_t			c;

	kernel_shell_init_contexts();
	active_screen = current_screen;
	while (1)
	{
		if (active_screen != current_screen)
			active_screen = current_screen;

		(void)keyboard_poll();
		kernel_shell_restore_prompt();

		if (!ks.kb_queue[0])
			continue;

		term_focus_on_prompt();

		c = ks.kb_queue[0];
		ks.kb_queue[0] = 0;

		context = kernel_shell_get_context();
		kernel_shell_handle_char(context, c);
	}
}

shell_context_t	*kernel_shell_get_context(void)
{
	return (&shell_contexts[current_screen]);
}

void	kernel_shell_clear_input(shell_context_t *context)
{
	context->length = 0;
	context->input[0] = '\0';
}

void	kernel_shell_restore_prompt(void)
{
	shell_context_t	*context;

	context = kernel_shell_get_context();
	if (!context->prompt_pending)
		return;
	kernel_printf(SHELL_PROMPT);
	context->prompt_pending = FALSE;
}

void	kernel_shell_handle_char(shell_context_t *context, i8_t c)
{
	if (c == ENTER || c == CARRIAGE_RET)
		kernel_shell_handle_enter(context);
	else if (c == BACKSPACE)
		kernel_shell_handle_backspace(context);
	else if (c == TAB)
	{
		for (size_t i = 0; i < TAB_LENGTH; i++)
			kernel_shell_handle_printable(context, ' ');
	}
	else
		kernel_shell_handle_printable(context, c);
}

void	kernel_shell_handle_enter(shell_context_t *context)
{
	context->input[context->length] = '\0';
	kernel_printf("\n");
	kernel_shell_clear_input(context);
	context->prompt_pending = TRUE;
}

void	kernel_shell_handle_backspace(shell_context_t *context)
{
	if (context->length == 0)
		return;
	context->length--;
	context->input[context->length] = '\0';
	kernel_printf("\b \b");
}

void	kernel_shell_handle_printable(shell_context_t *context, i8_t c)
{
	if (context->length >= MAX_INPUT_LENGTH)
		return;
	if (c < 32 || c >= 127)
		return;
	context->input[context->length++] = c;
	context->input[context->length] = '\0';

	kernel_printf("%c", c);
}

