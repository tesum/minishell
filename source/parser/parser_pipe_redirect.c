/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_pipe_redirect.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caugusta <caugusta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 16:12:48 by caugusta          #+#    #+#             */
/*   Updated: 2021/10/15 07:08:06 by caugusta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*redirect_handler(char const *input, int *i, int *this_is_redirect);
static int	set_redirect(char *str);

void	pipe_handler(int *i)
{
	t_list		*new_list;

	*i += 1;
	new_list = ft_lstnew((void *)command_new());
	if (new_list == NULL)
		exit_error("Malloc error", -1);
	ft_lstadd_back(&g_shell.cmd, (void *)new_list);
}

char	*double_redirect_handler(char const *input, int *i, \
	int *this_is_redirect)
{
	char	*redirect;
	char	*tmp;

	*this_is_redirect = 1;
	if ((input[*i] == '<' && input[(*i + 1)] == '<') || \
		(input[*i] == '>' && input[(*i + 1)] == '>'))
	{
		redirect = ft_substr(input, *i, 2);
		*i += 2;
		tmp = other_handler(input, i);
		if (redirect != NULL && tmp != NULL && !ft_strncmp(redirect, "<<", 2))
		{
			redirect = limiter_handler(redirect, tmp);
			if (redirect == NULL)
				return (NULL);
		}
		else
			redirect = ft_strjoin_gnl(redirect, tmp);
		try_free(tmp);
		if (set_redirect(redirect) == 0)
			return (redirect);
	}
	return (redirect_handler(input, i, this_is_redirect));
}

static char	*redirect_handler(char const *input, int *i, int *this_is_redirect)
{
	char	*redirect;
	char	*tmp;

	if ((input[*i] == '<' && *this_is_redirect != -1) || \
		(input[*i] == '>' && *this_is_redirect != -1))
	{
		redirect = ft_substr(input, *i, 1);
		*i += 1;
		tmp = other_handler(input, i);
		redirect = ft_strjoin_gnl(redirect, tmp);
		try_free(tmp);
		if (set_redirect(redirect) == 0)
			return (redirect);
	}
	if (*this_is_redirect == -1)
		exit_error("Malloc error", -1);
	return (NULL);
}

static int	set_redirect(char *str)
{
	t_command	*tmp;
	t_list		*new;

	if (str == NULL)
		exit_error("Malloc error", -1);
	tmp = (t_command *)ft_lstlast(g_shell.cmd)->content;
	new = ft_lstnew((void *)str);
	if (new == NULL)
		exit_error("Malloc error", -1);
	ft_lstadd_back(&tmp->redirect, new);
	return (0);
}
