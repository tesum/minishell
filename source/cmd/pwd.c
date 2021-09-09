/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsenijdrozdov <arsenijdrozdov@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 08:59:37 by arsenijdroz       #+#    #+#             */
/*   Updated: 2021/09/09 09:05:06 by arsenijdroz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(char **env)
{
	int		i;
	char	*pwd;

	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp(env[i], "PWD=", 4))
		{
			pwd = env[i] + 4;
			printf("%s\n", pwd);
			// ft_putstr_fd(pwd, 1);
		}
	}
	printf("Our func\n");
}
