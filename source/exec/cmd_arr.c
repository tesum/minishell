/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_arr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caugusta <caugusta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 15:59:22 by caugusta          #+#    #+#             */
/*   Updated: 2021/10/13 07:09:20 by caugusta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// #include "../includes/minishell.h"

int	get_cmd_char(char *cmd)
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

void	cmd_func(int cmd, char **cmd_ex)
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

void	cleaning(void)
{
	t_list	*tmp;

	while (g_shell.cmd)
	{
		ft_lstclear(&(((t_command *)g_shell.cmd->content)->argv), free);
		ft_lstclear(&(((t_command *)g_shell.cmd->content)->redirect), free);
		tmp = g_shell.cmd->next;
		ft_lstdelone(g_shell.cmd, free);
		g_shell.cmd = tmp;
	}
	g_shell.cmd = NULL;
	ft_lstadd_back(&g_shell.cmd, ft_lstnew((void *)command_new()));
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
