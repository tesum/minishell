/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demilan <demilan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 20:51:16 by demilan           #+#    #+#             */
/*   Updated: 2021/10/03 20:51:23 by demilan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	edit_pwd(t_env *env, char *pwd, char *oldpwd)
{
	edit_env_line(env, "PWD", pwd);
	edit_env_line(env, "OLDPWD", oldpwd);
}

void	ft_cd(char **argv)
{
	char	*oldpwd;
	char	*pwd;
	char	*buf;
	int		dir;

	buf = NULL;
	oldpwd = getcwd(buf, 0);
	dir = chdir(argv[1]);
	if (dir == -1)
	{
		ft_putendl_fd("No such file or directory", 2);
		return ;
	}
	pwd = getcwd(buf, 0);
	edit_pwd(g_shell.new_env, pwd, oldpwd);
	return ;
}
