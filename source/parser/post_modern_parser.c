/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_modern_parser.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caugusta <caugusta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 16:08:15 by caugusta          #+#    #+#             */
/*   Updated: 2021/10/11 18:32:08 by caugusta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	who_is_your_daddy(void)
{
	pid_t	pid;
	char	**cmd;

	cmd = set_command_struct(g_shell.cmd);
	if (cmd == NULL || builtins(cmd))
	{
		if (cmd != NULL)
			free_2d_arr(cmd);
		return ;
	}
	if (cmd != NULL)
		free_2d_arr(cmd);
	pid = fork();
	if (pid == 0)
		executing(g_shell.cmd);
	else
	{
		waitpid(pid, &g_shell.result, 0);
		g_shell.result /= 256;
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
			str = (void *)clear_quotes(((char *)tmp->content));
			if (!ft_strncmp(str, ">>", 2))
				g_shell.fd = open(str + 2, \
					O_WRONLY | O_CREAT | O_APPEND, 0666);
			else if (!ft_strncmp(str, ">", 1))
				g_shell.fd = open(str + 1, \
					O_WRONLY | O_CREAT | O_TRUNC, 0666);
			else if (!ft_strncmp(str, "<", 1))
			{
				g_shell.fd_r = open(str + 1, O_RDONLY, 0666);
				if (g_shell.fd_r < 0)
					exit_error("Error back-redirect", 254);
				dup2(g_shell.fd_r, 0);
				// close(g_shell.fd_r);
			}
			// if (g_shell.fd < 0)
			// {

			// }

			tmp = tmp->next;
			dup2(g_shell.fd, 1);
			close(g_shell.fd);
			free(str);
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
	tmp_arg = ((t_command *)pipe->content)->argv;
	cmd = NULL;
	if (tmp_arg != NULL)
	{
		cmd = malloc(sizeof(char *) * (ft_lstsize(tmp_arg) + 1));
		while (tmp_arg)
		{
			cmd[i] = clear_quotes((char *)tmp_arg->content);
			i++;
			tmp_arg = tmp_arg->next;
		}
		cmd[i] = NULL;
	}
	redirect_create(((t_command *)pipe->content));
	tmp->complete = 1;
	return (cmd);
}

char	*clear_quotes(char *input)
{
	int		i;
	char	*str;

	i = 0;
	str = ft_strdup(input);
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

// LEAKS!!
char	**env_arr(t_env *new_env, int export)
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
		if ((export && new_env->exp) || !export)
		{
			str = ft_strdup("");
			str = ft_strjoin_gnl(str, new_env->key);
			str = ft_strjoin_gnl(str, "=");
			str = ft_strjoin_gnl(str, new_env->value);
			env[j] = str;
		}
		j++;
		new_env = new_env->next;
	}
	return (env);
}
