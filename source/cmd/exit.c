#include "minishell.h"

void	ft_exit(char **argv)
{
	int	i;

	i = 0;
	while(argv[i] != NULL)
		i++;
	if (i > 2)
	{
		printf("exit: too many arguments");
		return ;
	}
	printf("exit");
	exit((unsigned char)ft_atoi(argv[1]));
}
