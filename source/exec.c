#include "minishell.h"

char	*correct_path(char **cmd)
{
	int		i;
	char	**path;
	char	*tmp;

	i = 0;
	if (access(cmd[0], X_OK) == 0) // not allowed
		return (cmd[0]);
	path = find_path();
	while (path[i])
	{
		path[i] = ft_strjoin_gnl(path[i], "/");
		path[i] = ft_strjoin_gnl(path[i], cmd[0]);
		if (path[i] == NULL)
			exit_error("Error malloc\n", -1);
		if (access(path[i], X_OK) == 0) // not allowed
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

void	executing(t_list *cmd)
{
	char	*str;
	char	*path;
	char	**_cmd;

	str = NULL;
	_cmd = set_command_struct(cmd);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	if (builtins(_cmd))
		exit(0);
	path = correct_path(_cmd);
	if (execve(path, _cmd, g_shell.env) == -1)
	{
		str = ft_strjoin_gnl(_cmd[0], ": command not found\n");
		if (str == NULL)
			exit_error("Error malloc\n", -1);
		exit_error(str, 127);
	}
	else
	{
		free (path);
		path = NULL;
	}
}

char	**free_2d_arr(char **arr)
{
	int	i;

	i = 0;
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
