/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caugusta <caugusta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 01:05:23 by demilan           #+#    #+#             */
/*   Updated: 2021/10/13 10:38:54 by caugusta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	child(int flag, t_pipex *pipex, int *a, int *b)
{
	if (!flag && pipex->iter == 0)
	{
		close(a[0]);
		dup2(a[1], 1);
		close(a[1]);
	}
	else if (!flag)
	{
		dup2(b[0], 0);
		close(a[0]);
		dup2(a[1], 1);
	}
	else if (flag)
	{
		dup2(a[0], 0);
		close(a[0]);
		close(b[0]);
		dup2(b[1], 1);
	}
}

static void	parent(int flag, t_list *cmd, int *a, int *b)
{
	if (!flag && !cmd->next)
	{
		close(a[0]);
		close(b[1]);
	}
	else if (flag && !cmd->next)
	{
		close(a[1]);
		close(b[0]);
	}
	if (!flag)
	{
		if (b[0])
			close(b[0]);
		close(a[1]);
	}
	else
	{
		close(a[0]);
		close(b[1]);
	}
}

static void	procces_pipe(t_pipex *pipex, int *a, int *b, pid_t *pid)
{
	pid[pipex->iter] = fork();
	if (!pid[pipex->iter])
	{
		if (!pipex->cmd->next)
		{
			if (!pipex->flag)
				dup2(b[0], 0);
			else
				dup2(a[0], 0);
			executing(pipex->cmd);
		}
		else
			child(pipex->flag, pipex, a, b);
		executing(pipex->cmd);
	}
	else
	{
		parent(pipex->flag, pipex->cmd, a, b);
		if (!pipex->flag && pipex->cmd->next)
			pipex->flag = 1;
		else if (pipex->flag && pipex->cmd->next)
			pipex->flag = 0;
	}
}

static void	if_have_next(t_pipex *pipex, int *a, int *b)
{
	if (pipex->cmd->next)
	{
		if (!pipex->flag)
			pipe(a);
		else
			pipe(b);
	}
}

void	pipes(int argc)
{
	int		a[2];
	int		b[2];
	t_pipex	pipex;
	pid_t	*pid;

	pipex.cmd = g_shell.cmd;
	pipex.flag = 0;
	pipex.iter = 0;
	pipex.c_pipe = argc;
	pid = malloc(sizeof(pid_t) * pipex.c_pipe);
	while (pipex.cmd)
	{
		if_have_next(&pipex, a, b);
		procces_pipe(&pipex, a, b, pid);
		pipex.cmd = pipex.cmd->next;
		pipex.iter++;
	}
	pipex.iter = 0;
	while (pipex.iter < pipex.c_pipe)
	{
		waitpid(pid[pipex.iter], &g_shell.result, 0);
		g_shell.result /= 256;
		pipex.iter++;
	}
	try_free(pid);
}
