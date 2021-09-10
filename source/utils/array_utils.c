#include "minishell.h"

char	**arr_add_back(char **array, char *content)
{
	char	**tmp;
	int		i;

	i = 0;
	if (array == NULL || content == NULL)
		return (NULL);
	tmp = malloc(sizeof(char *) * (arr_size(array) + 2));
	if (tmp == NULL)
		return (free_2d_arr(array));
	while (i < arr_size(array))
	{
		tmp[i] = ft_strdup(array[i]);
		if (tmp[i] == NULL)
		{
			free_2d_arr(array);
			return (free_2d_arr(tmp));
		}
		i++;
	}
	free_2d_arr(array);
	tmp[i] = ft_strdup(content);
	if (tmp[i] == NULL)
		return(free_2d_arr(tmp));
	tmp[i + 1] = NULL;
	return (tmp);
}

// char	**arr_add_front(char **array, char *content)
// {
// 	char	**tmp;
// 	int		i;

// 	i = 0;
// 	if (array == NULL || content == NULL)
// 		return (NULL);
// 	tmp = malloc(sizeof(char *) * (arr_size(array) + 2));
// 	if (tmp == NULL)
// 		return (free_2d_arr(array));
// 	tmp[i] = ft_strdup(content);
// 	if (tmp[i] == NULL)
// 	{
// 		free_2d_arr(tmp);
// 		return (free_2d_arr(array));
// 	}
// 	i++;
// 	while (i < arr_size(array) + 1)
// 	{
// 		tmp[i] = ft_strdup(array[i - 1]);
// 		if (tmp[i] == NULL)
// 			return (free_2d_arr(tmp));
// 		i++;
// 	}
// 	tmp[i] = NULL;
// 	return (tmp);
// }

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
	while (i < arr_size(array) + 1)
	{
		i++;
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