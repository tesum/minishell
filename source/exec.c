#include "minishell.h"

char	*correct_path(char **env, char **cmd)
{
	int		i;
	char	**path;
	char	*tmp;

	i = 0;
	if (access(cmd[0], X_OK) == 0)
		return (cmd[0]);
	path = find_path(env);
	while (path[i])
	{
		path[i] = ft_strjoin_gnl(path[i], "/");
		path[i] = ft_strjoin_gnl(path[i], cmd[0]);
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

char	**find_path(char **env)
{
	int		i;
	char	**path;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp("PATH=", env[i], 5) == 0)
			path = ft_split(env[i] + 5, ':');
		i++;
	}
	if (path == NULL)
		exit_error("Error malloc\n", -1);
	return (path);
}

void	executing(char **env, char **cmd)
{
	char	*str;
	char	*path;

	str = NULL;
	path = correct_path(env, cmd);
	if (execve(path, cmd, env) == -1)
	{
		str = ft_strjoin("Command '", cmd[0]);
		if (str == NULL)
			exit_error("Error malloc\n", -1);
		str = ft_strjoin_gnl(str, "' not found");
		if (str == NULL)
			exit_error("Error malloc\n", -1);
		exit_error(str, 0);
	}
	else
	{
		free (path);
		path = NULL;
		free_2d_arr(cmd);
	}
}

void	free_2d_arr(char **arr)
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
}

void	exit_error(char *str, int code)
{
	perror(str);
	exit (code);
}
