/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demilan <demilan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 16:03:40 by caugusta          #+#    #+#             */
/*   Updated: 2021/10/18 13:45:59 by demilan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	export_plus(t_env *env, char *key, char *value)
{
	t_env	*tmp;

	tmp = find_list_env(env, key);
	if (!tmp)
	{
		add_back_env(&env, new_env(key, 1, 1));
		tmp = find_list_env(env, key);
	}
	tmp->value = ft_strjoin_gnl(tmp->value, value);
	if (value)
		tmp->env = 1;
	tmp->exp = 1;
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
	export_get_value(arg, i, &value, f_plus);
	if (find_list_env(env, key) && !f_plus && f_eq)
		edit_env_line(env, key, value);
	else if (f_plus)
		export_plus(env, key, value);
	else if (f_eq)
		add_back_env(&env, new_env(arg, 1, 1));
	else if (!f_eq && find_list_env(env, key))
		NULL;
	else
		add_back_env(&env, new_env(arg, 0, 1));
	free(key);
	if (value)
		free(value);
}

void	edit_shlvl(t_env *env)
{
	int		num;
	t_env	*tmp;

	tmp = find_list_env(env, "SHLVL");
	if (tmp != NULL)
	{
		num = atoi(tmp->value);
		num += 1;
		try_free(tmp->value);
		tmp->value = ft_itoa(num);
	}
	else
	{
		tmp = new_env("SHLVL=1", 1, 1);
		if (tmp == NULL)
			exit_error("Error Malloc", -1);
		add_back_env(&env, tmp);
	}
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
