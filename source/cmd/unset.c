/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caugusta <caugusta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 20:52:26 by demilan           #+#    #+#             */
/*   Updated: 2021/10/19 11:36:36 by caugusta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	check_arg(char *arg)
{
	int	i;

	i = 0;
	if (!ft_isalpha(arg[i]) && arg[i] != '_')
		return (0);
	while (arg[i])
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static void	del_env_line(t_env *env, char *key)
{
	t_env	*iterator;
	t_env	*prev;

	if (env == NULL)
		return ;
	prev = env;
	iterator = prev->next;
	if (!ft_strncmp(prev->key, key, ft_strlen(key) + 1))
	{
		try_free3(prev->key, prev->value, prev);
		g_shell.new_env = iterator;
		return ;
	}
	while (iterator && ft_strncmp(iterator->key, key, ft_strlen(key) + 1))
	{
		prev = iterator;
		iterator = iterator->next;
	}
	if (iterator && !ft_strncmp(iterator->key, key, ft_strlen(key) + 1))
	{
		prev->next = iterator->next;
		try_free3(iterator->key, iterator->value, iterator);
	}
}

void	ft_unset(char **argv)
{
	int	i;
	int	res;

	i = 1;
	res = 0;
	while (argv[i])
	{
		if (!check_arg(argv[i]))
		{
			ft_putstr_fd("unset: '", 2);
			ft_putstr_fd(argv[i], 2);
			ft_putendl_fd("': not a valid identifier", 2);
			res = 1;
		}
		else
			del_env_line(g_shell.new_env, argv[i]);
		i++;
	}
	g_shell.result = res;
}
