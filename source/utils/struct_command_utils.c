#include "minishell.h"
t_command	*command_new(void)
{
	t_command	*new;

	new = malloc(sizeof(t_command));
	new->argv = NULL;
	new->redirect = NULL;
	new->complete = 0;
	return (new);
}
