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
		cmd = set_command_struct(g_shell.cmd);
		if (exec_ocmd(cmd))
			return ;
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

char	*get_pwd(void)
{
	int		i;
	char	**env;

	i = -1;
	env = g_shell.env;
	while (env[++i])
	{
		if (!ft_strncmp(env[i], "PWD=", 4))
			return (env[i] + 4);
	}
	return (NULL);
}

void	redirect_create(t_command *redirect)
{
	t_list	*tmp;
	
	tmp = redirect->redirect;
	while (tmp)
	{
		if (!ft_strncmp(((char **)tmp->content)[0], ">>", 2))
		{
			g_shell.fd = open(((char **)tmp->content)[1], O_WRONLY | O_CREAT | O_APPEND, 0666);
		}
		else
			g_shell.fd = open(((char **)tmp->content)[1], O_WRONLY| O_CREAT | O_TRUNC, 0666);
		tmp = tmp->next;
	}
	dup2(g_shell.fd, 1);
}

char	**set_command_struct(t_list *pipe)
{
	t_command	*tmp;
	t_list		*tmp_arg;
	char		**cmd;
	int	i;

	i = 0;
	tmp = (t_command *)pipe->content;
	// while (tmp->complete != 0)
	// {
	// 	pipe = pipe->next;
	// 	tmp = (t_command *)pipe->content;
	// }
	tmp_arg = ((t_command *)pipe->content)->argv;
	cmd = malloc(sizeof(char *) * (ft_lstsize(tmp_arg) + 1));
	while (tmp_arg)
	{
		cmd[i] = clear_quotes((char *)tmp_arg->content);
		i++;
		tmp_arg = tmp_arg->next;
	}
	cmd[i] = NULL;
	redirect_create(((t_command *)pipe->content));
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