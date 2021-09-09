#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	char	*input;

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
		else if (input != NULL)
		{
			free(input);
			input = NULL;
		}
	}
	ft_putstr_fd("exit\n", 1);
	return (0);
}

void	init_shell(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	// env"SHELL" = argv[0];
	// shlvl ++;
	g_shell.env = env;
	g_shell.result = 0;
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
