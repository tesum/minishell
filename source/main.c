/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsenijdrozdov <arsenijdrozdov@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 16:01:00 by caugusta          #+#    #+#             */
/*   Updated: 2021/10/18 11:27:27 by arsenijdroz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	parsing(void);
static void	init_shell(int argc, char **argv, char **env);

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
			try_dup2(g_shell.fd_1, 1), try_dup2(g_shell.fd_0, 0);
		}
		cleaning();
	}
	return (0);
}

static int	parsing(void)
{
	char	*input;

	signal(SIGQUIT, SIG_IGN), signal(SIGINT, &ctrl_c);
	g_shell.signal = 0;
	input = readline("minishell$ ");
	if (!input)
		return (-1);
	if (ft_strlen(input) == 0)
	{
		try_free(input);
		input = NULL;
		return (1);
	}
	add_history(input);
	if (preparser(input) != -1)
		parser(input);
	else
		return (1);
	try_free(input);
	return (0);
}

static void	init_shell(int argc, char **argv, char **env)
{
	t_command	*new;
	t_list		*new_list;

	(void)argc;
	(void)argv;
	g_shell.env = NULL;
	if (env[0] != NULL)
		g_shell.new_env = init_env(env);
	else
		g_shell.new_env = NULL;
	edit_shlvl(g_shell.new_env);
	g_shell.result = 0;
	g_shell.fd_1 = try_dup(1);
	g_shell.fd_0 = try_dup(0);
	new = command_new();
	new_list = ft_lstnew((void *)new);
	if (new_list == NULL)
		exit_error("Error malloc\n", -1);
	ft_lstadd_back(&g_shell.cmd, (void *)new_list);
}

void	ctrl_c(int signal)
{
	if (signal == SIGINT)
	{
		ft_putchar_fd('\n', 2);
		rl_replace_line("", 2);
		rl_on_new_line();
		rl_redisplay();
		g_shell.result = signal - 1;
	}
}
