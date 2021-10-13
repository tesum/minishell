/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_arr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caugusta <caugusta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 15:59:22 by caugusta          #+#    #+#             */
/*   Updated: 2021/10/13 10:53:21 by caugusta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_cmd_char(char *cmd)
{
	int		i;
	char	*cmds[8];

	i = -1;
	cmds[0] = "echo";
	cmds[1] = "cd";
	cmds[2] = "pwd";
	cmds[3] = "export";
	cmds[4] = "unset";
	cmds[5] = "env";
	cmds[6] = "exit";
	cmds[7] = NULL;
	while (cmds[++i])
	{
		if (ft_strnstr(cmds[i], cmd, ft_strlen(cmd)) && \
			ft_strlen(cmds[i]) == ft_strlen(cmd))
			return (i);
	}
	return (-1);
}

static void	cmd_func(int cmd, char **cmd_ex)
{
	void	(*cmds[8])(char **cmd);
	int		i;

	cmds[0] = ft_echo;
	cmds[1] = ft_cd;
	cmds[2] = ft_pwd;
	cmds[3] = ft_export;
	cmds[4] = ft_unset;
	cmds[5] = ft_env;
	cmds[6] = ft_exit;
	cmds[7] = NULL;
	i = -1;
	while (cmds[++i])
	{
		if (i == cmd)
			cmds[i](cmd_ex);
	}
}

int	builtins(char **cmd)
{
	int	i;
	int	j;

	i = -1;
	if (cmd != NULL)
	{
		j = get_cmd_char(cmd[0]);
		if (j != -1)
		{
			cmd_func(j, cmd);
			g_shell.result = 0;
			return (1);
		}
	}
	return (0);
}
