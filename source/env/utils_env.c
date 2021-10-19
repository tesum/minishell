/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caugusta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 08:46:06 by caugusta          #+#    #+#             */
/*   Updated: 2021/10/19 08:46:09 by caugusta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	env_size(t_env *env);

static char	*str_create(t_env *env)
{
	char	*str;

	str = ft_strjoin_gnl(ft_strdup(""), env->key);
	if (env->value)
	{
		str = ft_strjoin_gnl(str, "=");
		str = ft_strjoin_gnl(str, env->value);
	}
	if (str == NULL)
		exit_error("Error malloc", -1);
	return (str);
}

char	**env_arr(t_env *env, int export)
{
	char	**arr_env;
	int		i;
	int		j;
	int		k;

	if (env == NULL)
		return (NULL);
	i = env_size(env);
	arr_env = malloc(sizeof(char *) * (i + 1));
	if (arr_env == NULL)
		exit_error("Error malloc", -1);
	j = 0;
	k = 0;
	while (env && j < i)
	{
		if (!export && env->env)
			arr_env[k++] = str_create(env);
		else
			arr_env[k++] = str_create(env);
		j++;
		env = env->next;
	}
	arr_env[k] = NULL;
	return (arr_env);
}

void	edit_shlvl(t_env *env)
{
	int		num;
	t_env	*tmp;

	tmp = find_list_env(env, "SHLVL");
	if (tmp != NULL)
	{
		num = (int)ft_atoi(tmp->value);
		num += 1;
		try_free(tmp->value);
		tmp->value = ft_itoa(num);
	}
	else
	{
		tmp = new_env("SHLVL=1", 1, 1);
		if (tmp == NULL)
			exit_error("Error Malloc", -1);
		add_back_env(&g_shell.new_env, tmp);
	}
}

void	start_pwd(t_env *env)
{
	char	*pwd;
	char	*buf;
	t_env	*tmp;

	tmp = find_list_env(env, "PWD");
	buf = NULL;
	if (tmp == NULL)
	{
		pwd = getcwd(buf, 0);
		if (!pwd)
		{
			ft_putendl_fd(strerror(errno), 2);
			g_shell.result = 1;
			exit(-1);
		}
		edit_env_line(env, "PWD", pwd);
		try_free(pwd);
	}
}

static int	env_size(t_env *env)
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
