#include "minishell.h"

void	o_env(void)
{
	int	i;
	char	**env;

	i = -1;
	env = g_shell.env;
	while (env[++i])
	{
		ft_putstr_fd(env[i], 1);
	}
}
