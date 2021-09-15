#include "minishell.h"


void	put_env(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
	{
		ft_putstr_fd(env[i], STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
	}
}

void	o_env(char **argv)
{
	int	i;
	char	**env;

	(void)argv;
	i = -1;
	env = g_shell.env;
	
		put_env(g_shell.env);
}
