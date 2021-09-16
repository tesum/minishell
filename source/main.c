#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	char	*input = "pwd | pwd";

	rl_outstream = STDERR_FILENO;
	init_shell(argc, argv, env);
	while (1)
	{
		signal_handler();
		input = readline("minishell$ ");
		if (!input)
			break ;
		if (ft_strlen(input) == 0)
		{
			g_shell.result = 0;
			free(input);
			input = NULL;
			continue ;
		}
		add_history(input);
		if (preparser(input) != -1)
			parser(input);
		// pipes(argc, &input, g_shell.env);
		free(input);
		if (g_shell.error_malloc != 1)
		{
			// printf("%d\n",ft_lstsize(g_shell.cmd));
			if (ft_lstsize(g_shell.cmd) > 1)
			{
				// printf("%d\n",ft_lstsize(g_shell.cmd));
				// printf("here\n");
				pipes(argc, g_shell.env);
				dup2(g_shell.fd_1, 1);
				dup2(g_shell.fd_0, 0);
			}
			else
			{
				// printf("tut\n");				
				who_is_your_daddy();
			}
		}
		// exit (0);
	}
	ft_putstr_fd("exit\n", 1);
	return (0);
}

void	print_t_list(void)
{
	t_list		*tmp;
	t_command	*cmd;
	char		**rdir;
	int			i;

	tmp = g_shell.cmd;
	i = 0;
	while (tmp)
	{
		cmd = (t_command *)tmp->content;
		while (cmd->argv)
		{
			printf("argv[%d] = %s\n", i, (char *)cmd->argv->content);
			i++;
			cmd->argv = cmd->argv->next;
		}
		i = 0;
		while (cmd->redirect)
		{
			rdir =	(char **)cmd->redirect->content;
			printf("redirect[%d] = %s\n", i, rdir[0]);
			printf("redirect[%d] = %s\n", i, rdir[1]);
			i++;
			cmd->redirect = cmd->redirect->next;
		}
		printf("PIPE\n");
		tmp = tmp->next;
	}
}

void	init_shell(int argc, char **argv, char **env)
{
	t_command	*new;
	t_list		*new_list;

	(void)argc;
	(void)argv;
	// env"SHELL" = argv[0];
	// shlvl ++;
	g_shell.env = env;
	g_shell.result = 0;
	g_shell.error_malloc = 0;
	g_shell.pwd = get_pwd();
	g_shell.fd_1 = dup(1);
	g_shell.fd_0 = dup(0);
	new = command_new();
	new_list = ft_lstnew((void *)new);
	if (new_list == NULL)
		free(new);
	ft_lstadd_back(&g_shell.cmd, (void *)new_list);
}

void	signal_handler(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ctrl_c);
}

void	ctrl_c(int signal)
{
	(void)signal;
	ft_putchar_fd('\n', 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_shell.result = 1;
}
