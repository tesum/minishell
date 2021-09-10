#include "minishell.h"

int	redirect_input(char *file) // <
{
	int	fd;

	fd = open(file, O_RDONLY);
	dup2(, STDIN_FILENO);
}