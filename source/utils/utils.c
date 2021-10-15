/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caugusta <caugusta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 01:07:33 by demilan           #+#    #+#             */
/*   Updated: 2021/10/15 07:41:36 by caugusta         ###   ########.fr       */
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

void	status_handler(void)
{
	if (WIFEXITED(g_shell.result))
		g_shell.result = WEXITSTATUS(g_shell.result);
	if (WIFSIGNALED(g_shell.result))
		g_shell.result = 128 + WTERMSIG(g_shell.result);
}
