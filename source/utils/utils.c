/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demilan <demilan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 01:07:33 by demilan           #+#    #+#             */
/*   Updated: 2021/10/18 13:15:34 by demilan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	status_handler(void)
{
	if (WIFEXITED(g_shell.result))
		g_shell.result = WEXITSTATUS(g_shell.result);
	else if (WIFSIGNALED(g_shell.result))
	{
		g_shell.result = 128 + WTERMSIG(g_shell.result);
		ft_putchar_fd('\r', 2);
	}
}

int	try_dup(int fd)
{
	int	dupp;

	dupp = dup(fd);
	if (dupp == -1)
		exit_error(strerror(errno), 1);
	return (dupp);
}

int	try_dup2(int fd, int fd2)
{
	int	dupp;

	dupp = dup2(fd, fd2);
	if (dupp == -1)
		exit_error(strerror(errno), 1);
	return (dupp);
}
