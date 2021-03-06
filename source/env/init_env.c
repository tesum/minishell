/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demilan <demilan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 16:55:02 by caugusta          #+#    #+#             */
/*   Updated: 2021/10/18 13:48:47 by demilan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_new_env(t_env *new, char *str, int j)
{
	if (j != 0 && str[j])
	{
		new->value = ft_strdup(str + j);
		if (new->value == NULL)
			exit_error("Malloc error", -1);
	}
	else
	{
		new->key = ft_strdup(str);
		new->value = NULL;
		if (new->key == NULL)
			exit_error("Malloc error", -1);
	}
	new->next = NULL;
}

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
			exit_error("Malloc error", -1);
		envs = new_env(str, 1, 1);
		free(str);
	}
	while (env[++i])
	{
		str = ft_strdup(env[i]);
		if (str == NULL)
			exit_error("Malloc error", -1);
		new = new_env(str, 1, 1);
		add_back_env(&envs, new);
		free(str);
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
		exit_error("Malloc error", -1);
	i = -1;
	j = 0;
	while (str[++i])
	{
		if (str[i] == '=')
		{
			j = i + 1;
			new->key = ft_substr(str, 0, i);
			if (new->key == NULL)
				exit_error("Malloc error", -1);
		}
	}
	set_new_env(new, str, j);
	new->env = env;
	new->exp = exp;
	return (new);
}

void	add_back_env(t_env **env, t_env *new)
{
	t_env	*tmp;

	tmp = *env;
	if (new == NULL)
		exit_error("Malloc error", -1);
	if (tmp == NULL)
		*env = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

// utils env
void	edit_env_line(t_env *env, char *find, char *edit)
{
	t_env	*tmp;

	tmp = find_list_env(env, find);
	if (tmp == NULL)
	{
		tmp = new_env(find, 0, 1);
		if (tmp == NULL)
			exit_error("Error Malloc", -1);
		add_back_env(&g_shell.new_env, tmp);
	}
	if (edit)
	{
		tmp->env = 1;
		try_free(tmp->value);
		tmp->value = NULL;
		tmp->value = ft_strdup(edit);
		if (tmp->value == NULL)
			exit_error("Error Malloc", -1);
	}
}
