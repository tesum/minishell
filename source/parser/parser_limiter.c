/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_limiter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caugusta <caugusta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 09:20:41 by caugusta          #+#    #+#             */
/*   Updated: 2021/10/13 09:23:38 by caugusta         ###   ########.fr       */
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
		waitpid(pid, &g_shell.signal, 0);
	if (g_shell.signal != 0)
	{
		g_shell.result = g_shell.signal / 256;
		close(pip[0]), try_free(limiter), close(pip[1]);
		return (NULL);
	}
	try_free(limiter), close(pip[1]);
	return (ft_itoa(pip[0]));
}

static void	limiter_child(int *pip, char *limiter)
{
	char	*input;

	signal(SIGINT, ctrl_c_), close (pip[0]);
	while (1)
	{
		input = readline("> ");
		if (!input || !ft_strncmp(input, limiter, ft_strlen(limiter)))
			try_free(input), exit(0);
		ft_putendl_fd(input, pip[1]);
	}
}
