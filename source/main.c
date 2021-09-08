#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	char	*input;

	(void)argc;
	(void)argv;
	while (1)
	{
		input = readline("minishell$ ");
		if (ft_strlen(input) == 0)
			continue ;
		if (!input)
			break ;
		add_history(input);
		if (preparser(input) != -1)
			parser(input, env);
		else
			free(input);
	}
	return (0);
}
