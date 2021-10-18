/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_modern_parser.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsenijdrozdov <arsenijdrozdov@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 16:08:15 by caugusta          #+#    #+#             */
/*   Updated: 2021/10/18 11:27:35 by arsenijdroz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*quote_handler(char *input, int quote, int *i);
static char	*quote_helper(char *tmp_str2, int quote);

void	who_is_your_daddy(void)
{
	pid_t	pid;
	char	**cmd;

	cmd = set_command_struct(g_shell.cmd);
	if (cmd == NULL || builtins(cmd))
	{
		if (cmd)
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
		status_handler();
	}
}

char	*clear_quotes(char *input)
{
	int		i;
	char	*str;

	i = 0;
	str = ft_strdup(input);
	if (str == NULL)
		exit_error("Malloc error", -1);
	while (str && str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			str = quote_handler(str, str[i], &i);
		else if (str[i] == '$')
			str = dollar(str, &i);
		else
			i++;
	}
	if (str == NULL)
		exit_error("Malloc error", -1);
	return (str);
}

static char	*quote_handler(char *input, int quote, int *i)
{
	int		j;
	char	*tmp_str;
	char	*tmp_str2;
	char	*tmp_str3;

	input[*i] = '\0';
	j = ++(*i);
	tmp_str = ft_strdup(input);
	input[*i - 1] = quote;
	while (input[*i] != quote && input[*i] != '\0')
		(*i)++;
	tmp_str2 = ft_substr(input, j, *i - j);
	tmp_str3 = ft_strdup(input + (*i + 1));
	tmp_str2 = quote_helper(tmp_str2, quote);
	tmp_str = ft_strjoin_gnl(tmp_str, tmp_str2);
	*i = ft_strlen(tmp_str);
	tmp_str = ft_strjoin_gnl(tmp_str, tmp_str3);
	if (!tmp_str || !tmp_str2 || !tmp_str3)
		exit_error("Malloc error", -1);
	try_free(input), try_free(tmp_str2), try_free(tmp_str3);
	return (tmp_str);
}

static char	*quote_helper(char *tmp_str2, int quote)
{
	int	j;

	if (tmp_str2 == NULL)
		exit_error("Malloc error", -1);
	if (quote == 34)
	{
		j = 0;
		while (tmp_str2 != NULL && tmp_str2[j])
		{
			if (tmp_str2 != NULL && tmp_str2[j] == '$')
				tmp_str2 = dollar(tmp_str2, &j);
			else
				j++;
		}
	}
	return (tmp_str2);
}
