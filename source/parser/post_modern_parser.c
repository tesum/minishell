/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_modern_parser.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caugusta <caugusta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 16:08:15 by caugusta          #+#    #+#             */
/*   Updated: 2021/10/13 07:11:02 by caugusta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	who_is_your_daddy(void)
{
	pid_t	pid;
	char	**cmd;

	cmd = set_command_struct(g_shell.cmd);
	if (cmd == NULL || builtins(cmd))
	{
		if (cmd != NULL)
			free_2d_arr(cmd);
		return ;
	}
	if (cmd != NULL)
		free_2d_arr(cmd);
	pid = fork();
	if (pid == 0)
		executing(g_shell.cmd);
	else
	{
		waitpid(pid, &g_shell.result, 0);
		g_shell.result /= 256;
	}
}

char	*clear_quotes(char *input)
{
	int		i;
	char	*str;

	i = 0;
	str = ft_strdup(input);
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			str = quote_handler(str, str[i], &i);
		else if (str[i] == '$')
			str = dollar(str, &i);
		else
			i++;
	}
	return (str);
}
