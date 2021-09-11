#include "minishell.h"

// void	post_modern_parser(char *input, char **formated)
// {
// 	int	i;

// 	i = 1;
// 	while(formated[i])
// 	{
// 		if (formated[i - 1][0] == '>' && formated[i][0] == '|')
// 		{
// 			ft_putstr_fd("syntax error near unexpected token `|'", 2);
// 			free(input);
// 			input = NULL;
// 			free_2d_arr(formated);
// 			return ;
// 		}
// 		i++;
// 	}
// 	who_is_your_daddy(input, formated);
// }

// void	who_is_your_daddy(char *input, char **formated)
// {
// 	pid_t	pid;

// 	set_command_struct(formated);
// 	printf("%s\n", ((t_command *)(g_shell.cmd->content))->argv[0]);
// 	printf("%s\n", ((t_command *)(g_shell.cmd->content))->argv[1]);
// 	printf("%s\n", ((t_command *)(g_shell.cmd->content))->argv[2]);
// 	pid = fork();
// 	if (pid == 0)
// 		executing(formated);
// 	else
// 	{
// 		waitpid(pid, &g_shell.result, 0);
// 		g_shell.result /= 256;
// 		if (input != NULL)
// 			free (input);
// 		input = NULL;
// 		free_2d_arr(formated);
// 	}
// }

// void	set_command_struct(char **formated)
// {
// 	t_command	*tmp;
// 	int	i;

// 	i = 0;
// 	while (formated[i])
// 	{
// 		tmp = command_new(formated + i);
// 		if (tmp == NULL)
// 			return ;
// 		printf("SEG NOT AFTER NEW\n");
// 		ft_lstadd_back(&g_shell.cmd, ft_lstnew(tmp));
// 		printf("SEG NOT AFTER LST\n");
// 		// command_add_back(&g_shell.command, tmp);
// 		while (formated[i] && formated[i][0] != '|')
// 			i++;
// 		if (formated[i] && formated[i][0] == '|')
// 			i++;
// 		printf("SEG NOT\n");
// 	}
// }