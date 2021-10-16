/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsenijdrozdov <arsenijdrozdov@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 16:03:40 by caugusta          #+#    #+#             */
/*   Updated: 2021/10/15 13:50:03 by arsenijdroz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	export_plus(t_env *env, char *key, char *value)
{
	t_env	*tmp;

	tmp = find_list_env(env, key);
	tmp->value = ft_strjoin_gnl(tmp->value, value);
	if (value)
		tmp->env = 1;
	tmp->exp = 1;
}

int	check_value(char *value)
{
	int	i;

	i = 0;
	while (value[i] != '=')
	{
		i++;
	}
	if (!value[i])
		return (1);
	return (0);
}

void	logic_export(int *flags, int i, t_env *env, char *arg)
{
	char	*key;
	char	*value;
	int		f_eq;
	int		f_plus;

	f_plus = flags[0];
	f_eq = flags[1];
	key = ft_substr(arg, 0, i);
	// if (check_value(arg))
	// {
	// 	value = NULL;
	// }
	// else
	// {
		if (f_plus)
			value = ft_strdup(arg + i + 2);
			// value = ft_substr(arg, i + 2, ft_strlen(arg) - i);
		else
			value = ft_strdup(arg + i + 1);
	// }
		// value = ft_substr(arg, i + 1, ft_strlen(arg) - i);
	// if (!value)
	if (find_list_env(env, key) && !f_plus)
		edit_env_line(env, key, value);
	else if (find_list_env(env, key) && f_plus)
		export_plus(env, key, value);
	else if (f_eq)
		add_back_env(&env, new_env(arg, 1, 1));
	else
		add_back_env(&env, new_env(arg, 0, 1));
	free(key);
	// if (value)
	// 	free(value);
	// if (key)
	// 	try_free(key);
	// 	try_free(value);
}

t_env	*find_list_env(t_env *env, char *str)
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
	try_free(tmp->value);
	tmp->value = ft_itoa(num);
}

int	env_size(t_env *env)
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
