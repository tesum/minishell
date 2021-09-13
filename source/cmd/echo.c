#include "minishell.h"

void	echo(char	**argv)
{
	int	i;
	int	j;
	int	k;

	i = 1;
	j = 0;
	if (argv[i][0] == '-' && argv[i][1] == 'n')
	{
		i = flag_n(argv, i);
		while (argv[i][j])
		{
			if (argv[i][j] == '\n')
				k = j;
			j++;
		}
		j = k;
	}
	while (argv[i])
	{
		ft_putstr_fd(argv[i] + j, STDOUT_FILENO);
		j = 0;
		if (argv[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	ft_putchar_fd('\n', 1);
}

int		flag_n(char	**argv, int i)
{
	int	m;
	int	k;

	k = i;
	while(argv[i][0] == '-')
	{
		m = 1;
		while (argv[i][m] == 'n')
			m++;
		if (m != (int)ft_strlen(argv[i]))
			break ;
		(i)++;
	}
	if (i == k)
		return (k);
	else
		return(kill_n(argv, i));
}

int	kill_n(char **argv, int i)
{
	int	k;
	int	m;

	while (argv[i])
	{
		m = 0;
		while (argv[i][m] && argv[i][m] != '\n')
			m++;
		if (m != (int)ft_strlen(argv[i]))
			k = i;
		i++;
	}
	return (k);
}