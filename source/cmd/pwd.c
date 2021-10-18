/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsenijdrozdov <arsenijdrozdov@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 08:59:37 by arsenijdroz       #+#    #+#             */
/*   Updated: 2021/10/18 12:00:41 by arsenijdroz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(char **argv)
{
	char	*pwd;
	char	*buf;

	(void)argv;
	buf = NULL;
	pwd = getcwd(buf, 0);
	if (!pwd)
	{
		ft_putendl_fd(strerror(errno), 2);
		g_shell.result = 1;
		return ;
	}
	ft_putendl_fd(pwd, STDOUT_FILENO);
	try_free(pwd);
}
