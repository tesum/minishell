/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caugusta <caugusta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 16:01:00 by caugusta          #+#    #+#             */
/*   Updated: 2021/10/13 09:35:43 by caugusta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	int	status;

	rl_outstream = stderr;
	init_shell(argc, argv, env);
	while (1)
	{
		status = parsing();
		if (status == 1)
			continue ;
		if (status == -1)
		{
			ft_putendl_fd("exit", 2);
			exit (0);
		}
		if (g_shell.signal == 0)
		{
			if (ft_lstsize(g_shell.cmd) > 1)
				pipes(ft_lstsize(g_shell.cmd));
			else
				who_is_your_daddy();
			dup2(g_shell.fd_1, 1), dup2(g_shell.fd_0, 0);
		}
		cleaning();
	}
	return (0);
}

int	parsing(void)
{
	char	*input;

	signal(SIGQUIT, SIG_IGN), signal(SIGINT, ctrl_c);
	g_shell.signal = 0;
	input = readline("minishell$ ");
	if (!input)
		return (-1);
	if (ft_strlen(input) == 0)
	{
		free(input);
		input = NULL;
		return (1);
	}
	add_history(input);
	if (preparser(input) != -1)
		parser(input);
	else
		return (1);
	free(input);
	return (0);
}

void	init_shell(int argc, char **argv, char **env)
{
	t_command	*new;
	t_list		*new_list;

	(void)argc;
	(void)argv;
	g_shell.env = NULL;
	g_shell.new_env = init_env(env);
	edit_shlvl(g_shell.new_env);
	g_shell.result = 0;
	// g_shell.error_malloc = 0;
	g_shell.fd_1 = dup(1);
	g_shell.fd_0 = dup(0);
	new = command_new();
	new_list = ft_lstnew((void *)new);
	if (new_list == NULL)
		free(new);
	ft_lstadd_back(&g_shell.cmd, (void *)new_list);
}

void	ctrl_c(int signal)
{
	(void)signal;
	ft_putchar_fd('\n', 2);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_shell.result = 130;
}
