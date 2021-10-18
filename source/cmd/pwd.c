/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demilan <demilan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 08:59:37 by arsenijdroz       #+#    #+#             */
/*   Updated: 2021/10/18 16:22:49 by demilan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(char **argv)
{
	char	*pwd;
	char	*buf;
	t_env	*pwd_env;

	(void)argv;
	buf = NULL;
	pwd_env = find_list_env(g_shell.new_env, "PWD");
	if (pwd_env)
		pwd = pwd_env->value;
	else
		pwd = getcwd(buf, 0);
	if (!pwd)
	{
		ft_putendl_fd(strerror(errno), 2);
		g_shell.result = 1;
		return ;
	}
	ft_putendl_fd(pwd, STDOUT_FILENO);
}
