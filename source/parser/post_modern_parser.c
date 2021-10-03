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
	int		i;

	i = ft_lstsize(g_shell.cmd);
	while (i)
	{
		g_shell.env = env_arr(g_shell.new_env);
		cmd = set_command_struct(g_shell.cmd);
		if (builtins(cmd))
			return ;
		pid = fork();
		if (pid == 0)
			executing(g_shell.cmd);
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
	char	*str;

	tmp = redirect->redirect;
	if (tmp)
	{
		while (tmp)
		{
			str = clear_quotes(((char **)tmp->content)[1]);
			if (!ft_strncmp(((char **)tmp->content)[0], ">>", 3))
				g_shell.fd = open(str, O_WRONLY | O_CREAT | O_APPEND, 0666);
			else if (!ft_strncmp(((char **)tmp->content)[0], ">", 2))
				g_shell.fd = open(str, O_WRONLY| O_CREAT | O_TRUNC, 0666);
			else if (!ft_strncmp(((char **)tmp->content)[0], "<", 2))
			{
				g_shell.fd_r = open(str, O_RDONLY, 0666);
				if (g_shell.fd_r < 0)
					exit_error("Error back-redirect", 254);
				dup2(g_shell.fd_r, 0);
				close(g_shell.fd_r);
			}
			free(str);
			if (g_shell.fd < 0)
			{

			}
			tmp = tmp->next;
			dup2(g_shell.fd, 1);
			close(g_shell.fd);
		}
	}
}



char	**set_command_struct(t_list *pipe)
{
	t_command	*tmp;
	t_list		*tmp_arg;
	char		**cmd;
	int			i;

	i = 0;
	tmp = (t_command *)pipe->content;
	// while (tmp && tmp->complete != 0)   //// вот это говно не запускало команды
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

char	**env_arr(t_env *new_env)
{
	char	**env;
	char	*str;
	int		i;
	int		j;

	i = env_size(new_env);
	env = malloc(sizeof(char *) * (i + 1));
	j = 0;
	env[i] = NULL;
	while (j < i)
	{
		str = ft_strdup("");
		str = ft_strjoin_gnl(str, new_env->key);
		str = ft_strjoin_gnl(str, "=");
		str = ft_strjoin_gnl(str, new_env->value);
		env[j] = str;
		// printf("env[%d] = %s\n", j, env[j]);
		j++;
		new_env = new_env->next;
	}
	
	return (env);
}