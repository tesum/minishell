/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caugusta <caugusta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 16:55:15 by caugusta          #+#    #+#             */
/*   Updated: 2021/10/11 16:55:15 by caugusta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*dollar(char *input, int *i)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;
	int		j;

	j = ++(*i);
	while (input[*i] != '?' && ft_isdigit(input[*i]) != 1 \
		&& (ft_isalnum(input[j]) || input[j] == '_'))
		j++;
	if (j == *i && input[*i] != '?' && ft_isdigit(input[*i]) != 1)
		return (input);
	else if (input[*i] == '?' || ft_isdigit(input[*i]) == 1)
		j++;
	input[*i - 1] = '\0';
	tmp = ft_strdup(input);
	input[*i - 1] = '$';
	tmp2 = ft_substr(input, *i, j - *i);
	tmp2[ft_strlen(tmp2)] = '=';
	tmp2 = find_env(tmp2);
	tmp3 = ft_strdup(input + j);
	tmp = ft_strjoin_gnl(tmp, tmp2);
	*i = ft_strlen(tmp) - 1;
	tmp = ft_strjoin_gnl(tmp, tmp3);
	free(input), free(tmp2), free(tmp3);
	return (tmp);
}

char	*find_env(char *str)
{
	char	**env;
	int		i;
	int		j;

	i = 0;
	if (str == NULL)
		return (NULL);
	j = ft_strlen(str);
	env = g_shell.env;
	if (str[0] == '?')
	{
		free(str);
		return (ft_itoa(g_shell.result));
	}
	while (env[i])
	{
		if (ft_strncmp(env[i], str, j) == 0)
		{
			free(str);
			return (ft_strdup(env[i] + j));
		}
		i++;
	}
	free(str);
	return (ft_strdup(""));
}
