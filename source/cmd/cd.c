/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demilan <demilan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 20:51:16 by demilan           #+#    #+#             */
/*   Updated: 2021/10/18 14:47:46 by demilan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	edit_pwd(t_env *env, char *pwd, char *oldpwd)
{
	if (!find_list_env(env, "OLDPWD"))
		add_back_env(&g_shell.new_env, new_env("OLDPWD=", 1, 1));
	edit_env_line(env, "PWD", pwd);
	edit_env_line(env, "OLDPWD", oldpwd);
}

char	*change_to_dir(char *argv, t_env *env)
{
	char	*to_dir;

	to_dir = argv;
	if (!to_dir || !ft_strncmp(to_dir, "~", 1))
	{
		if (!find_list_env(env, "HOME"))
		{
			ft_putendl_fd("cd: HOME not set", 2);
			return (NULL);
		}
		to_dir = find_list_env(env, "HOME")->value;
	}
	if (!ft_strncmp(to_dir, "-", 1))
	{
		if (!find_list_env(env, "OLDPWD"))
		{
			ft_putendl_fd("cd: OLDPWD not set", 2);
			return (NULL);
		}
		to_dir = find_list_env(env, "OLDPWD")->value;
		ft_putendl_fd(to_dir, 1);
	}
	return (to_dir);
}

void	ft_cd(char **argv)
{
	char	*oldpwd;
	char	*pwd;
	char	*to_dir;
	int		dir;

	to_dir = change_to_dir(argv[1], g_shell.new_env);
	if (!to_dir)
		return ;
	oldpwd = getcwd(NULL, 0);
	dir = chdir(to_dir);
	if (dir == -1)
	{
		ft_putendl_fd(strerror(errno), 2);
		g_shell.result = 1;
		return ;
	}
	pwd = getcwd(NULL, 0);
	edit_pwd(g_shell.new_env, pwd, oldpwd);
	free(oldpwd);
	free(pwd);
}
