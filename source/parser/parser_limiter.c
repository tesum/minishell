/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_limiter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caugusta <caugusta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 09:20:41 by caugusta          #+#    #+#             */
/*   Updated: 2021/10/15 07:19:20 by caugusta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	limiter_child(int *pip, char *limiter);

char	*limiter_handler(char *rd, char *limiter)
{
	int		pip[2];
	pid_t	pid;

	try_free(rd), pipe(pip);
	pid = fork();
	if (pid == 0)
		limiter_child(pip, limiter);
	else
	{
		waitpid(pid, &g_shell.signal, 0);
		if (WIFSIGNALED(g_shell.result))
		{
			g_shell.signal = 1;
			g_shell.result = WTERMSIG(g_shell.result) - 1;
			close(pip[0]), try_free(limiter), close(pip[1]);
			return (NULL);
		}
	}
	close(pip[1]);
	limiter = ft_itoa(pip[0]);
	if (limiter == NULL)
		exit_error("Malloc error", -1);
	return (limiter);
}

static void	limiter_child(int *pip, char *limiter)
{
	char	*input;

	signal(SIGINT, SIG_DFL), close (pip[0]);
	while (1)
	{
		input = readline("> ");
		if (!input || !ft_strncmp(input, limiter, ft_strlen(limiter)))
			try_free(input), exit(0);
		ft_putendl_fd(input, pip[1]);
	}
}
