/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caugusta <caugusta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 16:03:40 by caugusta          #+#    #+#             */
/*   Updated: 2021/10/19 11:13:12 by caugusta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_get_value(char *arg, int i, char **value, int f_plus)
{
	int	j;

	j = 0;
	while (arg[j] != '\0')
	{
		if (arg[j] == '=')
			break ;
		j++;
	}
	if (arg[j] == '\0')
		*value = NULL;
	else
	{
		if (f_plus)
			*value = ft_strdup(arg + i + 2);
		else
			*value = ft_strdup(arg + i + 1);
		if (*value == NULL)
			exit_error("Malloc error", -1);
	}
}

static void	export_plus(t_env *env, char *key, char *value)
{
	t_env	*tmp;

	tmp = find_list_env(env, key);
	if (!tmp)
	{
		add_back_env(&g_shell.new_env, new_env(key, 1, 1));
		tmp = find_list_env(env, key);
	}
	if (value)
	{
		if (tmp->value)
			tmp->value = ft_strjoin_gnl(tmp->value, value);
		else
			tmp->value = ft_strjoin_gnl(ft_strdup(""), value);
	}
	else
		tmp->value = ft_strdup("");
	if (tmp->value == NULL)
		exit_error("Malloc error", -1);
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
		add_back_env(&g_shell.new_env, new_env(arg, 1, 1));
	else if (!f_eq && find_list_env(env, key))
		NULL;
	else
		add_back_env(&g_shell.new_env, new_env(arg, 0, 1));
	try_free(key);
	try_free(value);
}

t_env	*find_list_env(t_env *env, char *str)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, str, ft_strlen(str) + 1))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}
