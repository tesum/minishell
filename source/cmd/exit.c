#include "minishell.h"

void	o_exit(char **argv)
{
		(void)argv;

	ft_putstr_fd("Saving session...\n", 1);
	ft_putchar_fd('\n', 1);
	exit(1);
}