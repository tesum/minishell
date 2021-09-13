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

void	who_is_your_daddy(void)
{
	pid_t	pid;
	char	**cmd;
	int	i = ft_lstsize(g_shell.cmd);
	while (i)
	{
		cmd = set_command_struct();
		pid = fork();
		if (pid == 0)
			executing(cmd);
		else
		{
			waitpid(pid, &g_shell.result, 0);
			g_shell.result /= 256;
		}
		i--;
	}
}

char	**set_command_struct(void)
{
	t_command	*tmp;
	t_list		*pipe;
	char		**cmd;
	int	i;

	i = 0;
	pipe = g_shell.cmd;
	tmp = (t_command *)pipe->content;
	// while (tmp->complete != 0)
	// {
	// 	pipe = pipe->next;
	// 	tmp = (t_command *)pipe->content;
	// }
	cmd = malloc(sizeof(char *) * (ft_lstsize(tmp->argv) + 1));
	while (tmp->argv)
	{
		cmd[i] = clear_quotes((char *)tmp->argv->content);
		i++;
		tmp->argv = tmp->argv->next;
	}
	cmd[i] = NULL;
	tmp->complete = 1;
	return (cmd);
}

char	*clear_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			str = quote_handler(str, str[i], &i);
		else if (str[i] == '$')
			str = dollar(str, &i);
		else
			i++;
	}
	return (str);
}