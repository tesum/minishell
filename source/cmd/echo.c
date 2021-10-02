#include "minishell.h"

static int	flag_n(char	**argv, int i)
{
	int	m;

	while(argv[i][0] == '-')
	{
		m = 1;
		while (argv[i][m] == 'n')
			m++;
		if (m != (int)ft_strlen(argv[i]))
			break ;
		i++;
	}
	return (i);
}

void	ft_echo(char **argv)
{
	int	i;
	int	k;

	i = 1;
	k = 0;
	if (argv[i][0] == '-' && argv[i][1] == 'n')
	{
		i = flag_n(argv, i);
		k = 1;
	}
	while (argv[i])
	{
		ft_putstr_fd(argv[i], STDOUT_FILENO);
		if (argv[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (k == 0)
		ft_putchar_fd('\n', STDOUT_FILENO);
	g_shell.result = 0;
}
