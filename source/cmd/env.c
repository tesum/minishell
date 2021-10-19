/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demilan <demilan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 20:22:29 by demilan           #+#    #+#             */
/*   Updated: 2021/10/03 20:22:30 by demilan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	put_new_env(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (tmp->env == 1)
			printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}

void	ft_env(char **argv)
{
	(void)argv;
	put_new_env(g_shell.new_env);
}
