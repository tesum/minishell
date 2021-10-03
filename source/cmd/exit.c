#include "minishell.h"

static void	exit_sup(char **argv)
{
	int	i;

	ft_putendl_fd("exit", 2);
	i = 0;
	while(ft_isdigit(argv[1][i]))
		i++;
	if (argv[1][i] != '\0')
	{
		ft_putstr_fd(argv[1] ,2);
		ft_putendl_fd(": numeric argument required" ,2);
		exit(255);
	}
	exit((unsigned char)ft_atoi(argv[1]));
}

void	ft_exit(char **argv)
{
	int	i;

	i = 0;
	while(argv[i] != NULL)
		i++;
	if (i > 2)
	{
		ft_putendl_fd("exit: too many arguments", 2);
		return ;
	}
	else if (i == 1)
	{
		ft_putendl_fd("exit", 2);
		exit(0);
	}
	else
		exit_sup(argv);
}
