/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caugusta <caugusta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 07:11:59 by caugusta          #+#    #+#             */
/*   Updated: 2021/10/13 07:12:00 by caugusta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	preparser(char const *input)
{
	int	i;
	// int	quote;
	// int	flag;

	i = 0;
	if (check_begin(input) == -1)
		return (-1);
	// while (input[i])
	// {
	// 	if (input[i] == '\'' || input[i] == '\"')
	// 	{
	// 		quote = input[i];
	// 		while (input[i] != quote)
	// 			i++;
	// 	}
	// 	if (input[i] == '|' || input[i] == '<' || input[i] == '>')
	// 		flag = -1;
	// 	if (input[i] != '|' || input[i] != '<' || input[i] != '>' || !ft_isspace(input[i]))
	// 		flag = 0;
	// 	i++;
	// }
	return (0);
}

int	check_second_quote(char quote, char const *input, int *i)
{
	while (input[*i])
	{
		if (input[*i] == quote)
			return(++(*i));
		(*i)++;
	}
	return (-1);
}

int	check_begin(char const *input)
{
	int	i;

	i = 0;
	while (ft_isspace(input[i]))
		i++;
	if (input[i] == '\0')
		return (-1);
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
	check_invalid(input);
	return (0);
}

int	check_invalid(char const *input)
{
	int	i;

	i = 0;
	while (input[i])
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
		i++;
	}
	return (0);
}

//TODO: проверить что я тут вообще написал
//TODO: добавить обработку что после редиректа сразу пайп