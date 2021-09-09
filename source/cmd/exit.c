#include "minishell.h"

void	o_exit(void)
{
	ft_putstr_fd("Saving session...", 1);
	ft_putchar_fd('\n', 1);
	exit(1);
}