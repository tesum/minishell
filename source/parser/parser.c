#include "minishell.h"

void	parser(char *input, char **env)
{
	int		i;
	char	**formated;
	pid_t	pid;

	i = -1;
	while (input != NULL && input[++i])
	{
		if (input != NULL && input[i] == '\'')
			input = single_quote(input, &i);
		if (input != NULL && input[i] == '\"')
			input = double_quote(input, env, &i);
		if (input != NULL && input[i] == '$')
			input = dollar(input, env, &i);
		input = double_redirect_handler(input, &i);
		input = pipe_handler(input, &i);
		if (input != NULL && (input[i] == ' ' || input[i] == '\t'))
			input[i] = 127;
	}
	formated = ft_split(input, 127);
	pid = fork();
	if (pid == 0)
		executing(env, formated);
	else
		wait(NULL);
	free (input);
}

char	*double_quote(char *input, char **env, int *i)
{
	input = delete_simbol(input, i);
	if (input == NULL)
		return (NULL);
	while (input[*i] != '\"')
	{
		if (input != NULL && input[*i] == '$')
		{
			input = dollar(input, env, i);
			if (input == NULL)
				return (NULL);
		}
		else
			(*i)++;
	}
	input = delete_simbol(input, i);
	if (input == NULL)
		return (NULL);
	return (input);
}

char	*single_quote(char *input, int *i)
{
	input = delete_simbol(input, i);
	if (input == NULL)
		return (NULL);
	while (input[*i] != '\'')
		(*i)++;
	input = delete_simbol(input, i);
	if (input == NULL)
		return (NULL);
	return (input);
}

char	*delete_simbol(char *input, int *i)
{
	input[*i] = 127;
	(*i)++;
	return (input);
}

void	error_malloc(char *a, char *b, char *c)
{
	if (a != NULL)
	{
		free(a);
		a = NULL;
	}
	if (b != NULL)
	{
		free(b);
		b = NULL;
	}
	if (c != NULL)
	{
		free(c);
		c = NULL;
	}
	ft_putstr_fd("Error malloc", 2);
}
