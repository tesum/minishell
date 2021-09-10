#include "minishell.h"

void	parser(char *input)
{
	int		i;
	char	**formated;

	i = -1;
	while (input != NULL && input[++i])
	{
		if (input != NULL && input[i] == '\'')
			input = single_quote(input, &i);
		if (input != NULL && input[i] == '\"')
			input = double_quote(input, &i);
		if (input != NULL && input[i] == '$')
			input = dollar(input, &i);
		input = double_redirect_handler(input, &i);
		input = pipe_handler(input, &i);
		if (input != NULL && (input[i] == ' ' || input[i] == '\t'))
			input[i] = 127;
	}
	formated = ft_split(input, 127);
	if (formated == NULL)
	{
		error_malloc(input, NULL, NULL);
		return ;
	}
	post_modern_parser(input, formated);
}

char	*double_quote(char *input, int *i)
{
	input = delete_simbol(input, i);
	while (input != NULL && input[*i] != '\"')
	{
		if (input != NULL && input[*i] == '$')
			input = dollar(input, i);
		// if (input != NULL && (input[*i] == '>' || input[*i] == '<' || \
		// 	input[*i] == '|'))
		// 	input = replace_str(input, "'|", i, (*i + 1));
		else
			(*i)++;
	}
	input = delete_simbol(input, i);
	return (input);
}

char	*single_quote(char *input, int *i)
{
	input = delete_simbol(input, i);
	while (input != NULL && input[*i] != '\'')
		(*i)++;
	input = delete_simbol(input, i);
	return (input);
}

char	*delete_simbol(char *input, int *i)
{
	if (input == NULL)
		return (NULL);
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
	g_shell.result = -1;
	ft_putstr_fd("Error malloc", 2);
}
