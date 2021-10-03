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

void	export_no_oper(t_env *env, char *str)
{
	t_env	*tmp;
	char	*value;

	value = ft_strdup(str);
	tmp = find_list_env(env, value);
	if (tmp == NULL)
	{
		tmp = new_env(value, 0, 1);
		add_back_env(&env, tmp);
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
	if (tmp == NULL)
	{
		tmp = new_env(value, 1, 1);
		free(key);
		add_back_env(&env, tmp);
		return ;
	}
	tmp->key = value;
	tmp->env = 1;
	tmp->exp = 1;
	free(key);
}

t_env	*find_list_env(t_env *env, char *str) //TODO: а если нет равно.
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		// printf("%s\n", tmp->key);
		if (!ft_strncmp(tmp->key, str, ft_strlen(str)))
			return (tmp);
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