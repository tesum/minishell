/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demilan <demilan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 08:59:37 by arsenijdroz       #+#    #+#             */
/*   Updated: 2021/10/18 15:02:31 by demilan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(char **argv)
{
	char	*pwd;
	char	*buf;

	(void)argv;
	buf = NULL;
	pwd = find_list_env(g_shell.new_env, "PWD")->value;
	if (!pwd)
		pwd = getcwd(buf, 0);
	if (!pwd)
	{
		ft_putendl_fd(strerror(errno), 2);
		g_shell.result = 1;
		return ;
	}
	ft_putendl_fd(pwd, STDOUT_FILENO);
}
