/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caugusta <caugusta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 16:54:36 by caugusta          #+#    #+#             */
/*   Updated: 2021/10/13 10:44:41 by caugusta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	set_arg(char *str, int *this_is_redirect);

void	parser(char const *input)
{
	int		i;
	int		this_is_redirect;
	char	*tmp;

	i = 0;
	this_is_redirect = 0;
	while (input[i] && input[i] != '|')
	{
		while (ft_isspace(input[i]))
			i++;
		if (input[i] == '<' || input[i] == '>')
			tmp = double_redirect_handler(input, &i, &this_is_redirect);
		else if (input[i] == '|')
		{
			pipe_handler(&i);
			continue ;
		}
		else
			tmp = other_handler(input, &i);
		if (g_shell.signal != 0)
			return ;
		if (set_arg(tmp, &this_is_redirect) == -1)
			try_free(tmp);
	}
}

static int	set_arg(char *str, int *this_is_redirect)
{
	t_command	*tmp;
	t_list		*new;

	if (str == NULL)
		exit_error("Malloc error", -1);
	if (*this_is_redirect == 1)
	{
		*this_is_redirect = 0;
		return (0);
	}
	if (ft_strlen(str) == 0)
		return (-1);
	tmp = (t_command *)ft_lstlast(g_shell.cmd)->content;
	new = ft_lstnew((void *)str);
	if (new == NULL)
		exit_error("Malloc error", -1);
	ft_lstadd_back(&tmp->argv, new);
	return (0);
}

char	*other_handler(char const *input, int *i)
{
	int		j;
	int		quote;

	if (input[*i] == '\0')
		return (ft_strdup(""));
	while (ft_isspace(input[*i]))
		(*i)++;
	j = *i;
	while (input[*i] != '<' && input[*i] != '>' && input[*i] != '|' && \
		!ft_isspace(input[*i]) && input[*i])
	{
		if (input[*i] == '\'' || input[*i] == '\"')
		{
			quote = input[*i];
			while (input[++(*i)] != quote)
				;
		}
		(*i)++;
	}
	return (ft_substr(input, j, *i - j));
}
