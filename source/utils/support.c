/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caugusta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 16:48:18 by caugusta          #+#    #+#             */
/*   Updated: 2021/10/18 16:48:20 by caugusta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	err_msg(char *str)
{
	ft_putstr_fd(str + 1, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(errno), 2);
}

void	sup_dup(int *fd)
{
	try_dup2(fd[1], 1);
	try_dup2(fd[0], 0);
	close(fd[0]);
	close(fd[1]);
}
