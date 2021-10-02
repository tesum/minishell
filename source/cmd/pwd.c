/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caugusta <caugusta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 08:59:37 by arsenijdroz       #+#    #+#             */
/*   Updated: 2021/10/02 19:31:06 by caugusta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(char **argv)
{
	(void)argv;
	ft_putstr_fd(g_shell.pwd, STDOUT_FILENO);
	ft_putstr_fd("\n", 1);
}
