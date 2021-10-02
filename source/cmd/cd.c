#include "minishell.h"

void	ft_cd(char **argv)
{
		(void)argv;
	opendir(argv[1]);
	
	return ;
}
