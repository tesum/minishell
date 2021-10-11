/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caugusta <caugusta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 16:54:36 by caugusta          #+#    #+#             */
/*   Updated: 2021/10/11 18:20:34 by caugusta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			if (pipe_handler(&i) == -1)
				return ;
			continue ;
		}
		else
			tmp = other_handler(input, &i);
		if (set_arg(tmp, &this_is_redirect) == -1 && tmp != NULL)
			free(tmp);
		if (g_shell.error_malloc == 1)
			return ;
	}
}

int	set_arg(char *str, int *this_is_redirect)
{
	t_command	*tmp;
	t_list		*new;

	if (str == NULL)
	{
		g_shell.error_malloc = 1;
		return (-1);
	}
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
	{
		g_shell.error_malloc = 1;
		return (-1);
	}
	ft_lstadd_back(&tmp->argv, new);
	return (0);
}

static char	*quote_helper(char *tmp_str2, int quote)
{
	int	j;

	if (quote == 34)
	{
		j = 0;
		while (tmp_str2 != NULL && tmp_str2[j])
		{
			if (tmp_str2 != NULL && tmp_str2[j] == '$')
				tmp_str2 = dollar(tmp_str2, &j);
			else
				j++;
		}
	}
	return (tmp_str2);
}

char	*quote_handler(char *input, int quote, int *i)
{
	int		j;
	char	*tmp_str;
	char	*tmp_str2;
	char	*tmp_str3;

	input[*i] = '\0';
	j = ++(*i);
	tmp_str = ft_strdup(input);
	input[*i - 1] = quote;
	while (input[*i] != quote && input[*i] != '\0')
		(*i)++;
	tmp_str2 = ft_substr(input, j, *i - j);
	tmp_str3 = ft_strdup(input + (*i + 1));
	tmp_str2 = quote_helper(tmp_str2, quote);
	tmp_str = ft_strjoin_gnl(tmp_str, tmp_str2);
	*i = ft_strlen(tmp_str);
	tmp_str = ft_strjoin_gnl(tmp_str, tmp_str3);
	free(input);
	free(tmp_str2);
	free(tmp_str3);
	return (tmp_str);
}

char	*other_handler(char const *input, int *i)
{
	int		j;
	char	*tmp;
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
	tmp = ft_substr(input, j, *i - j);
	return (tmp);
}
