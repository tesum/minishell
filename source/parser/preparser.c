/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caugusta <caugusta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 07:11:59 by caugusta          #+#    #+#             */
/*   Updated: 2021/10/13 13:05:49 by caugusta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_second_quote(char quote, char const *input, int *i);
static int	check_begin(char const *input);
static int	check_invalid(char const *input);
static int	lexer(const char *str, int *i);

int	preparser(char const *input)
{
	int	i;

	i = 0;
	if (check_begin(input) == -1)
		return (-1);
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '\"')
			check_second_quote(input[i], input, &i);
		if (lexer(input, &i) == -1)
		{
			ft_putendl_fd("Syntax error near unexpected token", 2);
			return (-1);
		}
		i++;
	}
	return (0);
}

static int	check_second_quote(char quote, char const *input, int *i)
{
	(*i)++;
	while (input[*i])
	{
		if (input[*i] == quote)
			return (++(*i));
		(*i)++;
	}
	return (-1);
}

static int	check_begin(char const *input)
{
	int	i;

	i = 0;
	while (ft_isspace(input[i]))
		i++;
	if (input[i] == '\0')
		return (-1);
	if (input[i] == '|')
	{
		ft_putendl_fd("Syntax error near unexpected token `|'", 2);
		return (-1);
	}
	if (input[i] == ';')
	{
		ft_putendl_fd("Syntax error near unexpected token `;'", 2);
		return (-1);
	}
	i = check_invalid(input);
	return (i);
}

static int	check_invalid(char const *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '\"')
		{
			if (check_second_quote('\"', input, &i) == -1)
			{
				ft_putendl_fd("Syntax error expected second \"", 2);
				return (-1);
			}
		}
		if (input[i] == '\'')
		{
			if (check_second_quote('\'', input, &i) == -1)
			{
				ft_putendl_fd("Syntax error expected second \'", 2);
				return (-1);
			}
		}
		i++;
	}
	return (0);
}

static int	lexer(const char *str, int *i)
{
	if (str[*i] == '|')
	{
		while (ft_isspace(str[++(*i)]))
			;
		if (str[*i] == '\0' || str[*i] == '|')
			return (-1);
	}
	if (str[*i] == '<' || str[*i] == '>')
	{
		(*i)++;
		if (str[*i] != str[*i - 1] && (str[*i] == '<' || str[*i] == '>'))
			return (-1);
		if (str[*i] == str[*i - 1])
			(*i)++;
		while (ft_isspace(str[*i]))
			(*i)++;
		if (str[*i] == '\0' || str[*i] == '|' || \
			str[*i] == '<' || str[*i] == '>')
			return (-1);
	}
	return (0);
}
