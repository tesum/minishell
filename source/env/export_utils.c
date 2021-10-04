#include "minishell.h"

void	export_plus(t_env *env, char *key, char *value)
{
	t_env	*tmp;

	tmp = find_list_env(env, key);
	tmp->value = ft_strjoin_gnl(tmp->value, value);
	if (value)
		tmp->env = 1;
	tmp->exp = 1;
}

t_env	*find_list_env(t_env *env, char *str) //TODO: а если нет равно.
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strlen(tmp->key) == ft_strlen(str))
		{
			if (!ft_strncmp(tmp->key, str, ft_strlen(str)))
				return (tmp);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

void	edit_shlvl(t_env *env)
{
	int		num;
	t_env	*tmp;

	tmp = find_list_env(env, "SHLVL");
	num = atoi(tmp->value);
	num += 1;
	free(tmp->value);
	tmp->value = ft_itoa(num);
}

void	clear_env(t_env **env)
{
	if ((*env)->next)
		clear_env(&(*env)->next);
	free((*env)->key);
	free((*env)->value);
	(*env)->next = NULL;
	free((*env));
	(*env) = NULL;
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
