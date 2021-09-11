#include "minishell.h"

int	preparser(char *input)
{
	int	i;

	i = -1;
	if (check_begin(input) == -1)
		return (-1);
	while (input[++i])
	{
		if (input[i] == '\"')
		{
			if (check_second_quote('\"', input, &i) == -1)
			{
				ft_putstr_fd("syntax error expected second \"\n", 2);
				return (-1);
			}
		}
		if (input[i] == '\'')
		{
			if (check_second_quote('\'', input, &i) == -1)
			{
				ft_putstr_fd("syntax error expected second \'\n", 2);
				return (-1);
			}
		}
	}
	return (0);
}

int	check_second_quote(char quote, char *input, int *i)
{
	while (input[++(*i)])
	{
		if (input[(*i)] == '$' && input[(*i) + 1] == '\"')
		{
			*i += 2;
			if (check_second_quote('\"', input, i) == -1)
				return (-1);
		}
		if (input[(*i)] == '$' && input[(*i) + 1] == '\'')
		{
			*i += 2;
			if (check_second_quote('\'', input, i) == -1)
				return (-1);
		}
		if (input[(*i)] == '\\' && input[(*i) + 1] == '\'')
			*i += 2;
		if (input[(*i)] == '\\' && input[(*i) + 1] == '\"')
			*i += 2;
		if (input[(*i)] == quote)
			return (0);
	}
	return (-1);
}

int	check_begin(char *input)
{
	int	i;

	i = 0;
	while (ft_isspace(input[i]))
		i++;
	if (input[i] == '|')
	{
		ft_putstr_fd("syntax error near unexpected token `|'\n", 2);
		return (-1);
	}
	if (input[i] == ';')
	{
		ft_putstr_fd("syntax error near unexpected token `;'\n", 2);
		return (-1);
	}
	int	flag = 0;
	i = 0;
	while (input[i])
	{
		while (input[i] && (input[i] != '>' || input[i] != '<' || \
			input[i] != '|'))
			i++;
		if (input[i] == '>' || input[i] == '<' || input[i] == '|')
		{
			flag = 1;
			i++;
		}
		while (ft_isspace(input[i]))
			i++;
		if (input[i] != '\0')
			flag = 0;
	}
	if (flag == 1)
	{
		ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
		return (-1);
	}
	return (0);
}


//TODO: проверить что я тут вообще написал
//TODO: добавить обработку что после редиректа сразу пайп