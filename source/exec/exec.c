/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caugusta <caugusta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 15:59:59 by caugusta          #+#    #+#             */
/*   Updated: 2021/10/19 12:06:24 by caugusta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_access(char *str)
{
	int	code;
	DIR	*dir;

	if (str && (str[0] == '.' || str[0] == '/'))
	{
		dir = opendir(str);
		if (dir)
		{
			closedir(dir);
			ft_putstr_fd(str, 2);
			exit_error(": is a directory", 126);
		}
		code = access(str, F_OK);
		if (code == -1)
			return (0);
		code = access(str, X_OK);
		if (code == -1)
		{
			ft_putstr_fd(str, 2);
			ft_putstr_fd(": ", 2);
			exit_error(strerror(errno), 126);
		}
		return (1);
	}
	return (0);
}

static char	**find_path(void)
{
	int		i;
	char	**path;

	i = 0;
	path = NULL;
	if (g_shell.env == NULL)
		return (NULL);
	while (g_shell.env[i])
	{
		if (ft_strncmp("PATH=", g_shell.env[i], 5) == 0)
		{
			path = ft_split(g_shell.env[i] + 5, ':');
			if (path == NULL)
				exit_error("Error malloc", -1);
			break ;
		}
		i++;
	}
	return (path);
}

static char	*correct_path(char **cmd)
{
	int		i;
	char	**path;
	char	*tmp;

	i = 0;
	if (ft_access(cmd[0]) != 0)
		return (cmd[0]);
	path = find_path();
	while (path && path[i])
	{
		path[i] = ft_strjoin_gnl(path[i], "/");
		path[i] = ft_strjoin_gnl(path[i], cmd[0]);
		if (path[i] == NULL)
			exit_error("Error malloc", -1);
		if (ft_access(path[i]) == 1)
		{
			tmp = ft_strdup(path[i]);
			if (tmp == NULL)
				exit_error("Error malloc", -1);
			free_2d_arr(path);
			return (tmp);
		}
		i++;
	}
	return (NULL);
}

void	executing(t_list *lst_cmd)
{
	char	*path;
	char	**cmd;

	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	cmd = set_command_struct(lst_cmd);
	if (cmd == NULL || builtins(cmd))
		exit(g_shell.result);
	path = correct_path(cmd);
	if (path == NULL)
	{
		ft_putstr_fd(cmd[0], 2);
		ft_putstr_fd(": ", 2);
		exit_error("command not found", 127);
	}
	if (execve(path, cmd, g_shell.env) == -1)
	{
		ft_putstr_fd(cmd[0], 2);
		ft_putstr_fd(": ", 2);
		exit_error(strerror(errno), errno);
	}
}
