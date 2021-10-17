/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caugusta <caugusta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 20:51:16 by demilan           #+#    #+#             */
/*   Updated: 2021/10/15 12:03:25 by caugusta         ###   ########.fr       */
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
	if (!argv[1] || !ft_strncmp(argv[1], "~", 1))
		argv[1] = find_list_env(g_shell.new_env, "HOME")->value;
	if (!argv[1] || !ft_strncmp(argv[1], "-", 1))
	{
		argv[1] = find_list_env(g_shell.new_env, "OLDPWD")->value;
		ft_putendl_fd(argv[1], 1);
	}
	oldpwd = getcwd(buf, 0);
	dir = chdir(argv[1]);
	if (dir == -1)
	{
		ft_putendl_fd(strerror(errno), 2);
		g_shell.result = 1;
		return ;
	}
	pwd = getcwd(buf, 0);
	edit_pwd(g_shell.new_env, pwd, oldpwd);
	return ;
}
