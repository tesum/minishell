/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caugusta <caugusta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 20:20:44 by demilan           #+#    #+#             */
/*   Updated: 2021/10/19 11:36:04 by caugusta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	export_sort(char **exp)
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

static char	**sort_export(char **exp)
{
	int		i;
	char	*tmp;

	while (1)
	{
		if (!export_sort(exp))
			break ;
		i = 0;
		while (exp[i + 1] != NULL)
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

static	int	check_arg(char *arg, t_env *env, int i)
{
	int		flags[2];

	flags[0] = 0;
	flags[1] = 0;
	while (arg[i])
	{
		if (arg[i] && !ft_isalnum(arg[i]) && arg[i] != '_')
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
			return (0);
		}
		i++;
	}
	logic_export(flags, i, env, arg);
	return (1);
}

void	put_export(void)
{
	char	**exp;
	int		i;

	if (!g_shell.new_env)
		return ;
	exp = env_arr(g_shell.new_env, 1);
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
	int	res;

	i = 1;
	res = 0;
	if (argv[1])
	{
		while (argv[i])
		{
			if ((!ft_isalpha(argv[i][0]) && argv[i][0] != '_') || \
				!check_arg(argv[i], g_shell.new_env, 1))
			{
				ft_putstr_fd("export: '", 2);
				ft_putstr_fd(argv[i], 2);
				ft_putendl_fd("': not a valid identifier", 2);
				res = 1;
			}
			i++;
		}
	}
	else
		put_export();
	g_shell.result = res;
}
