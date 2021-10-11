/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caugusta <caugusta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 20:20:44 by demilan           #+#    #+#             */
/*   Updated: 2021/10/11 17:30:17 by caugusta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export_sort(char **exp)
{
	int	i;

	i = 0;
	while (exp[i + 1])
	{
		if (exp[i][0] > exp[i + 1][0])
			return (1);
		i++;
	}
	return (0);
}

char	**sort_export(char **exp)
{
	int		i;
	char	*tmp;

	while (1)
	{
		if (!export_sort(exp))
			break ;
		i = 0;
		while (exp[i + 1] != '\0')
		{
			if (exp[i][0] < exp[i + 1][0])
				i++;
			else
			{
				tmp = exp[i];
				exp[i] = exp[i + 1];
				exp[i + 1] = tmp;
				i++;
			}
		}
	}
	return (exp);
}

static	int	check_arg(char *arg, t_env *env)
{
	int		i;
	int		*flags;

	i = 0;
	if (!ft_isalpha(arg[i]) && arg[i] != '-')
		return (0);
	flags = malloc(sizeof(int) * 2);
	flags[0] = 0;
	flags[1] = 0;
	while (arg[++i])
	{
		if (arg[i] == '+' && arg[i + 1] == '=')
		{
			flags[0] = 1;
			break ;
		}
		if (arg[i] == '=')
		{
			flags[1] = 1;
			break ;
		}
	}
	logic_export(flags, i, env, arg);
	return (1);
}

void	put_export(t_env *env)
{
	char	**exp;
	int		i;

	exp = env_arr(env, 1);
	exp = sort_export(exp);
	i = 0;
	while (exp[i])
	{
		ft_putendl_fd(exp[i], STDOUT_FILENO);
		i++;
	}
	free_2d_arr(exp);
}

void	ft_export(char **argv)
{
	int	i;

	i = 1;
	if (argv[1])
	{
		while (argv[i])
		{
			if (check_arg(argv[i], g_shell.new_env))
				;
			else
			{
				ft_putendl_fd("export: not a valid identifier", 2);
				return ;
			}
			i++;
		}
	}
	else
		put_export(g_shell.new_env);
	return ;
}
