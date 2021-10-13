/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caugusta <caugusta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 01:07:33 by demilan           #+#    #+#             */
/*   Updated: 2021/10/13 10:59:32 by caugusta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	ctrl_c_(int signal)
{
	(void)signal;
	ft_putchar_fd('\r', 2);
	rl_on_new_line();
	rl_replace_line("", 0);
	exit(130);
}
