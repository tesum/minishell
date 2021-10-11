/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caugusta <caugusta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 01:07:33 by demilan           #+#    #+#             */
/*   Updated: 2021/10/11 18:00:48 by caugusta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// parsing main
int	parsing(void)
{
	char	*input;

	signal_handler();
	input = readline("minishell$ ");
	if (!input)
		return (-1);
	if (ft_strlen(input) == 0)
	{
		g_shell.result = 0;
		free(input);
		input = NULL;
		return (1);
	}
	add_history(input);
	if (preparser(input) != -1)
		parser(input);
	else
		return (1);
	free(input);
	return (0);
}

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
		free(key);
	if (value)
		free(value);
	free(flags);
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

void	error_malloc(char *a, char *b, char *c)
{
	if (a != NULL)
	{
		free(a);
		a = NULL;
	}
	if (b != NULL)
	{
		free(b);
		b = NULL;
	}
	if (c != NULL)
	{
		free(c);
		c = NULL;
	}
	g_shell.result = -1;
	ft_putstr_fd("Error malloc", 2);
}

