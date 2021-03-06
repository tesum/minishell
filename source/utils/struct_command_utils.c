/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_command_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caugusta <caugusta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 16:04:57 by caugusta          #+#    #+#             */
/*   Updated: 2021/10/16 14:21:57 by caugusta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*command_new(void)
{
	t_command	*new;

	new = malloc(sizeof(t_command));
	if (new == NULL)
		exit_error("Error malloc", -1);
	new->argv = NULL;
	new->redirect = NULL;
	return (new);
}

static int	help_redirect(char *str, int *fd)
{
	if (!ft_strncmp(str, ">>", 2))
		fd[1] = open(str + 2, O_WRONLY | O_CREAT | O_APPEND, 0666);
	else if (!ft_strncmp(str, ">", 1))
		fd[1] = open(str + 1, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	else if (!ft_strncmp(str, "<", 1))
	{
		if (access(str + 1, R_OK) != 0)
		{
			err_msg(str);
			g_shell.result = 1;
			return (-1);
		}
		fd[0] = open(str + 1, O_RDONLY);
	}
	else
		fd[0] = (int)ft_atoi(str);
	if (fd[0] < 0 || fd[1] < 0)
	{
		err_msg(str);
		return (-1);
	}
	return (0);
}

static int	redirect_create(t_list *tmp)
{
	char	*str;
	int		fd[2];

	fd[0] = try_dup(0);
	fd[1] = try_dup(1);
	if (tmp)
	{
		while (tmp)
		{
			str = (void *)clear_quotes(((char *)tmp->content));
			if (str == NULL)
				exit_error("Error malloc", -1);
			if (help_redirect(str, fd) < 0)
			{
				try_free(str);
				return (-1);
			}
			try_free(str);
			tmp = tmp->next;
		}
		sup_dup(fd);
	}
	return (0);
}

static char	**argv_create(t_list *tmp_arg)
{
	char	**cmd;
	int		i;

	i = 0;
	cmd = NULL;
	if (tmp_arg != NULL)
	{
		cmd = malloc(sizeof(char *) * (ft_lstsize(tmp_arg) + 1));
		if (cmd == NULL)
			exit_error("Error malloc", -1);
		while (tmp_arg)
		{
			cmd[i] = clear_quotes((char *)tmp_arg->content);
			if (cmd[i] == NULL)
				exit_error("Error malloc", -1);
			i++;
			tmp_arg = tmp_arg->next;
		}
		cmd[i] = NULL;
	}
	return (cmd);
}

char	**set_command_struct(t_list *lst_cmd)
{
	if (g_shell.env != NULL)
		g_shell.env = free_2d_arr(g_shell.env);
	if (g_shell.new_env != NULL)
		g_shell.env = env_arr(g_shell.new_env, 0);
	if (redirect_create(((t_command *)lst_cmd->content)->redirect) < 0)
		return (NULL);
	return (argv_create(((t_command *)lst_cmd->content)->argv));
}
