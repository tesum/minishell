#include "minishell.h"

t_env	*init_env(char **env)
{
	int		i;
	char	*str;
	t_env	*envs;

	i = 0;
	if (env != NULL && env[0] != NULL)
	{
		str = ft_strdup(env[i]);
		if (str == NULL)
			exit_malloc_error();
		envs = new_env(str, 1, 1);
	}
	while (env[++i])
	{
		str = ft_strdup(env[i]);
		if (str == NULL)
			exit_malloc_error();
		add_back_env(&envs, new_env(str, 1, 1));
	}
	return (envs);
}

t_env	*new_env(char *str, int env, int exp)
{
	int		i;
	int		j;
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (new == NULL)
		return (NULL);
	i = -1;
	j = 0;
	while (str[++i])
	{
		if (str[i] == '=')
		{
			j = i + 1;
			new->key = ft_substr(str, 0, i);
		}
	}
	if (j != 0)
		new->value = ft_substr(str, j, i);
	else
	{
		new->key = ft_substr(str, 0, i);
		new->value = ft_strdup("");
	}
	new->env = env;
	new->exp = exp;
	new->next = NULL;
	return (new);
}

void	add_back_env(t_env **env, t_env *new)
{
	t_env	*tmp;

	tmp = *env;
	if (tmp == NULL)
		*env = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	exit_malloc_error(void)
{
	ft_putstr_fd("Error malloc", 2);
	exit (-1);
}

void	edit_env_line(t_env *env, char *find, char *edit)
{
	t_env	*tmp;

	// printf("fff\n");
	tmp = find_list_env(env, find);
	// printf("fff\n");
	if (edit)
		tmp->env = 1;
	tmp->value = edit;
}

int		env_size(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}