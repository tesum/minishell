/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caugusta <caugusta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 01:07:33 by demilan           #+#    #+#             */
/*   Updated: 2021/10/13 10:10:29 by caugusta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// utils for export
void	logic_export(int *flags, int i, t_env *env, char *arg)
{
	char	*key;
	char	*value;
	int		f_eq;
	int		f_plus;

	f_plus = flags[0];
	f_eq = flags[1];
	key = ft_substr(arg, 0, i);
	if (f_plus)
		value = ft_substr(arg, i + 2, ft_strlen(arg) - i);
	else
		value = ft_substr(arg, i + 1, ft_strlen(arg) - i);
	if (find_list_env(env, key) && !f_plus)
		edit_env_line(env, key, value);
	else if (find_list_env(env, key) && f_plus)
		export_plus(env, key, value);
	else if (f_eq)
		add_back_env(&env, new_env(arg, 1, 1));
	else
		add_back_env(&env, new_env(arg, 0, 1));
	if (key)
		try_free(key);
	if (value)
		try_free(value);
}

// utils env
void	edit_env_line(t_env *env, char *find, char *edit)
{
	t_env	*tmp;

	tmp = find_list_env(env, find);
	if (edit)
		tmp->env = 1;
	free(tmp->value);
	tmp->value = edit;
}

char	**env_arr(t_env *new_env, int export)
{
	char	**env;
	char	*str;
	int		i;
	int		j;

	i = env_size(new_env);
	env = malloc(sizeof(char *) * (i + 1));
	j = 0;
	env[i] = NULL;
	while (j < i)
	{
		if ((export && new_env->exp) || !export)
		{
			str = ft_strdup("");
			str = ft_strjoin_gnl(str, new_env->key);
			str = ft_strjoin_gnl(str, "=");
			str = ft_strjoin_gnl(str, new_env->value);
			env[j] = str;
		}
		j++;
		new_env = new_env->next;
	}
	return (env);
}

void	try_free(void *target)
{
	if (target == NULL)
		return ;
	free(target);
	target = NULL;
}

void	ctrl_c_(int signal)
{
	(void)signal;
	ft_putchar_fd('\r', 2);
	rl_on_new_line();
	rl_replace_line("", 0);
	exit(130);
}
