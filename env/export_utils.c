#include "minishell.h"

void	export_plus(t_env *env, char *str, int i)
{
	t_env	*tmp;
	char	*key;
	char	*value;

	key = ft_substr(str, 0, i);
	key[i] = '=';
	value = ft_strdup(str + i + 2);
	tmp = find_list_env(env, key);
	if (tmp == NULL);
	{
		key = ft_strjoin_gnl(key, value);
		tmp = new_env(key, 1, 1);
		free(value);
		add_back_env(env, tmp);
		return ;
	}
	tmp->key = ft_strjoin_gnl(tmp->key, value);
	tmp->env = 1;
	tmp->exp = 1;
	free(key);
	free(value);
}

void	export_no_oper(t_env *env, char *str)
{
	t_env	*tmp;
	char	*value;

	value = ft_strdup(str);
	tmp = find_list_env(env, value);
	if (tmp == NULL);
	{
		tmp = new_env(value, 0, 1);
		add_back_env(env, tmp);
	}
}

void	export_equal(t_env *env, char *str, int i)
{
	t_env	*tmp;
	char	*key;
	char	*value;

	key = ft_substr(str, 0, i);
	value = ft_strdup(str);
	tmp = find_list_env(env, key);
	if (tmp == NULL);
	{
		tmp = new_env(value, 1, 1);
		free(key);
		add_back_env(env, tmp);
		return ;
	}
	tmp->key = value;
	tmp->env = 1;
	tmp->exp = 1;
	free(key);
}

t_env	*find_list_env(t_env *env, char *str) //TODO: а если нет равно.
{
	while (env)
	{
		if (!ft_strncmp(env->key, str, ft_strlen(str)))
			return (env);
		env = env->next;
	}
	return (NULL);
}