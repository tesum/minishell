#include "minishell.h"

char	**arr_add_back(char **array, char *content)
{
	char	**tmp;
	int		i;
	int		size;

	i = 0;
	if (content == NULL)
		return (NULL);
	if (array == NULL)
	{
		tmp = malloc(sizeof(char *) * 2);
		if (tmp == NULL)
			return (NULL);
		size = 2;
	}
	else
	{
		write(1, "here\n", 5);
		size = (arr_size(array) + 2);
		tmp = malloc(sizeof(char *) * size);
		if (tmp == NULL)
			return (free_2d_arr(array));
	}
	if (array)
	{
		while (i < size)
		{
			tmp[i] = ft_strdup(array[i]);
			if (tmp[i] == NULL)
			{
				free_2d_arr(array);
				return (free_2d_arr(tmp));
			}
			i++;
		}
		// free_2d_arr(array);
	}
	tmp[i] = ft_strdup(content);
	if (tmp[i] == NULL)
		return(free_2d_arr(tmp));
	tmp[i + 1] = NULL;
	return (tmp);
}

char	**arr_del_str(char **array, char *str)
{
	char	**tmp;
	int		i;
	int		j;

	i = -1;
	j = 0;
	if (*array == NULL || str == NULL)
		return (NULL);
	tmp = malloc(sizeof(char *) * (arr_size(array) + 1));
	if (tmp == NULL)
		return (NULL);
	while (++i < arr_size(array))
	{
		if (!ft_strncmp(array[i], str, ft_strlen(str)))
			continue;
		tmp[j] = ft_strdup(array[i]);
		if (tmp[j] == NULL)
			return (free_2d_arr(tmp));
		j++;
	}
	tmp[i] = NULL;
	return (tmp);
}

char	**arr_copy_n_elem(char **array, int n)
{
	char	**tmp;
	int		i;

	i = 0;
	if (array == NULL)
		return (NULL);
	tmp = malloc(sizeof(char *) * (n + 1));
	if (tmp == NULL)
		return (NULL);
	while (i < n)
	{
		tmp[i] = ft_strdup(array[i]);
		if (tmp[i] == NULL)
			return (free_2d_arr(tmp));
		i++;
	}
	tmp[i] = ft_strdup(array[i]);
	if (tmp[i] == NULL)
		return(free_2d_arr(tmp));
	tmp[i + 1] = NULL;
	return (tmp);
}

int	arr_size(char **array)
{
	int		i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

void	print_t_list(void)
{
	t_list		*tmp;
	t_command	*cmd;
	char		**rdir;
	int			i;

	tmp = g_shell.cmd;
	i = 0;
	while (tmp)
	{
		cmd = (t_command *)tmp->content;
		while (cmd->argv)
		{
			printf("argv[%d] = %s\n", i, (char *)cmd->argv->content);
			i++;
			cmd->argv = cmd->argv->next;
		}
		i = 0;
		while (cmd->redirect)
		{
			rdir = (char **)cmd->redirect->content;
			printf("redirect[%d] = %s\n", i, rdir[0]);
			printf("redirect[%d] = %s\n", i, rdir[1]);
			i++;
			cmd->redirect = cmd->redirect->next;
		}
		printf("PIPE\n");
		tmp = tmp->next;
	}
}
