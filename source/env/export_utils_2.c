/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caugusta <caugusta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 13:55:21 by demilan           #+#    #+#             */
/*   Updated: 2021/10/18 17:09:07 by caugusta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*find_list_env(t_env *env, char *str)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strlen(tmp->key) == ft_strlen(str))
		{
			if (!ft_strncmp(tmp->key, str, ft_strlen(str)))
				return (tmp);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

int	check_value(char *value)
{
	int	i;

	i = 0;
	while (value[i] != '=')
	{
		i++;
	}
	if (!value[i])
		return (1);
	return (0);
}

void	export_get_value(char *arg, int i, char **value, int f_plus)
{
	if (check_value(arg))
	{
		*value = NULL;
	}
	else
	{
		if (f_plus)
			*value = ft_strdup(arg + i + 2);
		else
			*value = ft_strdup(arg + i + 1);
		if (*value == NULL)
			exit_error("Malloc error", -1);
	}
}
