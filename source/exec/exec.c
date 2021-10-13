/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caugusta <caugusta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 15:59:59 by caugusta          #+#    #+#             */
/*   Updated: 2021/10/13 09:47:30 by caugusta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*correct_path(char **cmd)
{
	int		i;
	char	**path;
	char	*tmp;

	i = 0;
	if (access(cmd[0], X_OK) == 0)
		return (cmd[0]);
	path = find_path();
	while (path[i])
	{
		path[i] = ft_strjoin_gnl(path[i], "/");
		path[i] = ft_strjoin_gnl(path[i], cmd[0]);
		if (path[i] == NULL)
			exit_error("Error malloc\n", -1);
		if (access(path[i], X_OK) == 0)
		{
			tmp = ft_strdup(path[i]);
			if (tmp == NULL)
				exit_error("Error malloc\n", -1);
			free_2d_arr(path);
			return (tmp);
		}
		i++;
	}
	return (NULL);
}

char	**find_path(void)
{
	int		i;
	char	**path;

	i = 0;
	path = NULL;
	while (g_shell.env[i])
	{
		if (ft_strncmp("PATH=", g_shell.env[i], 5) == 0)
		{
			path = ft_split(g_shell.env[i] + 5, ':');
			break ;
		}
		i++;
	}
	if (path == NULL)
		exit_error("Error malloc\n", -1);
	return (path);
}

void	executing(t_list *lst_cmd)
{
	char	*str;
	char	*path;
	char	**cmd;

	signal(SIGQUIT, SIG_DFL), signal(SIGINT, ctrl_c_);
	str = NULL;
	cmd = set_command_struct(lst_cmd);
	if (cmd == NULL || builtins(cmd))
		exit(g_shell.result);
	path = correct_path(cmd);
	if (execve(path, cmd, g_shell.env) == -1)
	{
		str = ft_strjoin_gnl(cmd[0], ": command not found\n");
		if (str == NULL)
			exit_error("Error malloc\n", -1);
		exit_error(str, 127);
	}
}

char	**free_2d_arr(char **arr)
{
	int	i;

	i = 0;
	if (arr == NULL)
		return (NULL);
	while (arr[i] != NULL)
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
	arr = NULL;
	return (arr);
}

void	exit_error(char *str, int code)
{
	ft_putstr_fd(str, 2);
	exit (code);
}
