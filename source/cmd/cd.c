#include "minishell.h"

void	cd(char **argv)
{
		(void)argv;
	opendir(argv[1]);
	
	return ;
}
