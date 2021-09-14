#include "minishell.h"

int	check_arg(char *arg, char ***env)
{
	int	i;
	int	r;

	i = 0;
	r = 0;
	if (arg[i] == '=')
		return (0);
	while(arg[i])
	{
		if (arg[i] == '=')
			r = 1;
		if (arg[i] && r == 1)
		{
			*env = arr_add_back(*env, arg);
			return (1);
		}
		i++;
	}
	return (0);
}

void	return_err(void)
{
	ft_putstr_fd("env: No such file or directory\n", 2);
	return ;
}

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

// transport to export
void	o_env(char **argv)
{
	int	i;
	char	**env;

	(void)argv;
	i = -1;
	env = g_shell.env;
	if (argv[1])
	{
		if (check_arg(argv[1], &env))
		{
			g_shell.env = env;
			put_env(g_shell.env);
		}
		else
			return_err();
	}
	else
		put_env(g_shell.env);
}
