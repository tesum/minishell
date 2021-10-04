#include "minishell.h"

t_env	*init_env(char **env)
{
	int		i;
	char	*str;
	t_env	*envs;
	t_env	*new;

	i = 0;
	if (env != NULL && env[0] != NULL)
	{
		str = ft_strdup(env[i]);
		if (str == NULL)
			exit_malloc_error();
		envs = new_env(str, 1, 1);
		free(str);
	}
	while (env[++i])
	{
		str = ft_strdup(env[i]);
		if (str == NULL)
			exit_malloc_error();
		new = new_env(str, 1, 1);
		add_back_env(&envs, new);
		free(str);
	}
	return (envs);
}

void	set_new_env(t_env *new, char *str, int i, int j)
{
	if (j != 0)
		new->value = ft_substr(str, j, i);
	else
	{
		new->key = ft_substr(str, 0, i);
		new->value = ft_strdup("");
	}
	new->next = NULL;
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
	set_new_env(new, str, i, j);
	new->env = env;
	new->exp = exp;
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

