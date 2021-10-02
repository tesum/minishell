#include "minishell.h"

t_env	*init_env(char **env)
{
	int		i;
	char	*str;
	t_env	*new;
	t_env	*envs;

	i = 0;
	envs = NULL;
	while (env[i])
	{
		str = ft_strdup(env[i]);
		if (str == NULL)
			exit_malloc_error();
		new = new_env(str, 1, 1);
		add_back_env(&envs, new);
	}
	return (envs);
}

t_env	*new_env(char *key, int env, int exp)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (new == NULL)
		return (NULL);
	new->key = key;
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
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	exit_malloc_error(void)
{
	ft_putstr_fd("Error malloc", 2);
	exit (-1);
}
