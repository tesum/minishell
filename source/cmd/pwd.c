/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demilan <demilan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 08:59:37 by arsenijdroz       #+#    #+#             */
/*   Updated: 2021/09/14 17:57:48 by demilan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(char **argv)
{
	int		i;
	char	**env;

	(void)argv;
	i = -1;
	env = g_shell.env;
	while (env[++i])
	{
		if (!ft_strncmp(env[i], "PWD=", 4))
		{
			ft_putstr_fd(env[i] + 4, STDOUT_FILENO);
			ft_putstr_fd("\n", 1);
		}
	}
}
