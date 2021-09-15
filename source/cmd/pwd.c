/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demilan <demilan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 08:59:37 by arsenijdroz       #+#    #+#             */
/*   Updated: 2021/09/15 13:40:31 by demilan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(char **argv)
{
	(void)argv;
	ft_putstr_fd(g_shell.pwd, STDOUT_FILENO);
	ft_putstr_fd("\n", 1);
}
