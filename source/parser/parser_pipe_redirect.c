#include "minishell.h"

char	*pipe_handler(char *input, int *i)
{
	if (input != NULL && input[*i] == '|')
	{
		input[*i] = '\0';
		input = replace_str(input, " | ", i, (*i + 1));
	}
	if (input != NULL && input[*i] == ' ')
		input[*i] = 127;
	if (input != NULL && input[*i - 2] == ' ')
		input[*i - 2] = 127;
	return (input);
}

char	*double_redirect_handler(char *input, int *i)
{
	if (input != NULL && input[*i] == '<' && input[(*i + 1)] == '<')
	{
		input[*i] = '\0';
		input = replace_str(input, " << ", i, (*i + 2));
		if (input != NULL && input[*i] == ' ')
			input[*i] = 127;
		if (input != NULL && input[*i - 3] == ' ')
			input[*i - 3] = 127;
		return (input);
	}
	if (input != NULL && input[*i] == '>' && input[(*i + 1)] == '>')
	{
		input[*i] = '\0';
		input = replace_str(input, " >> ", i, (*i + 2));
		if (input != NULL && input[*i - 1] == ' ')
			input[*i] = 127;
		if (input != NULL && input[*i - 3] == ' ')
			input[*i - 3] = 127;
		return (input);
	}
	return (redirect_handler(input, i));
}

char	*redirect_handler(char *input, int *i)
{
	if (input != NULL && input[*i] == '<')
	{
		input[*i] = '\0';
		input = replace_str(input, " < ", i, (*i + 1));
		if (input != NULL && input[*i] == ' ')
			input[*i] = 127;
		if (input != NULL && input[*i - 2] == ' ')
			input[*i - 2] = 127;
		return (input);
	}
	if (input != NULL && input[*i] == '>')
	{
		input[*i] = '\0';
		input = replace_str(input, " > ", i, (*i + 1));
		if (input != NULL && input[*i] == ' ')
			input[*i] = 127;
		if (input != NULL && input[*i - 2] == ' ')
			input[*i - 2] = 127;
		return (input);
	}
	return (input);
}

char	*replace_str(char *input, char *str_replace, int *start, int end)
{
	char	*tmp1;
	char	*tmp2;

	if (str_replace == NULL)
		return (NULL);
	tmp1 = ft_strdup(input);
	tmp2 = ft_strdup(input + end);
	if (tmp1 == NULL || tmp2 == NULL)
	{
		error_malloc(tmp1, tmp2, input);
		return (NULL);
	}
	free(input);
	input = NULL;
	tmp1 = ft_strjoin_gnl(tmp1, str_replace);
	tmp1 = ft_strjoin_gnl(tmp1, tmp2);
	if (tmp1 == NULL)
	{
		error_malloc(tmp1, tmp2, input);
		return (NULL);
	}
	free (tmp2);
	*start += ft_strlen(str_replace) - 1;
	input = tmp1;
	return (input);
}
