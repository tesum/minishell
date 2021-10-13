/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_pipe_redirect.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caugusta <caugusta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 16:12:48 by caugusta          #+#    #+#             */
/*   Updated: 2021/10/13 05:04:53 by caugusta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipe_handler(int *i)
{
	t_command	*new;
	t_list		*new_list;

	*i += 1;
	new = command_new();
	if (new == NULL)
		return (-1);
	new_list = ft_lstnew((void *)new);
	if (new_list == NULL)
	{
		free(new);
		return (-1);
	}
	ft_lstadd_back(&g_shell.cmd, (void *)new_list);
	return (0);
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
		if (!ft_strncmp(redirect, "<<", 2))
			redirect = limiter_handler(redirect, tmp);
		else
		{
			redirect = ft_strjoin_gnl(redirect, tmp);
			free(tmp);
		}
		if (set_redirect(redirect, this_is_redirect) == 0)
			return (redirect);
	}
	if (*this_is_redirect == -1)
		error_malloc(redirect, NULL, NULL);
	return (redirect_handler(input, i, this_is_redirect));
}

char	*redirect_handler(char const *input, int *i, int *this_is_redirect)
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
		free(tmp);
		if (set_redirect(redirect, this_is_redirect) == 0)
			return (redirect);
	}
	if (*this_is_redirect == -1)
		error_malloc(tmp, NULL, NULL);
	return (NULL);
}

int	set_redirect(char *str, int *this_is_redirect)
{
	t_command	*tmp;
	t_list		*new;

	if (str == NULL)
	{
		*this_is_redirect = -1;
		return (-1);
	}
	tmp = (t_command *)ft_lstlast(g_shell.cmd)->content;
	new = ft_lstnew((void *)str);
	if (new == NULL)
	{
		*this_is_redirect = -1;
		return (-1);
	}
	ft_lstadd_back(&tmp->redirect, new);
	return (0);
}

char	*limiter_handler(char *rd, char *limiter)
{
	int		pip[2];
	pid_t	pid;
	char	*input;

	free(rd), pipe(pip);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL), close (pip[0]);
		while (1)
		{
			input = readline("> ");
			if (!input || !ft_strncmp(input, limiter, ft_strlen(limiter)))
				free(input), exit(0);
			ft_putendl_fd(input, pip[1]);
		}
	}
	else
		waitpid(pid, &g_shell.result, 0);
	g_shell.result /= 256;
	if (g_shell.result != 0)
		g_shell.error_malloc = 1;
	free(limiter), close(pip[1]);
	return (ft_itoa(pip[0]));
}
