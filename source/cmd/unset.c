#include "minishell.h"

static	int	check_arg(char *arg)
{
	int	i;
	int	r;

	i = 0;
	r = 0;
	if (arg[i] == '=')
		return (1);
	while (arg[i])
	{
		if (arg[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

void	unset(char **argv)
{
	int	i;

	i = 1;
	if (argv[1])
	{
		while (argv[i])
		{
			if (check_arg(argv[i]))
			{
				ft_putstr_fd("unset: Invalid parameter name\n", 2);
				return ;
			}
			else
				g_shell.env = arr_del_str(g_shell.env, argv[i]);
			i++;
		}
	}
	return ;

}
