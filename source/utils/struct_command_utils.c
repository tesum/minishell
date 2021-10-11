/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_command_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caugusta <caugusta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 16:04:57 by caugusta          #+#    #+#             */
/*   Updated: 2021/10/11 16:05:01 by caugusta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*command_new(void)
{
	t_command	*new;

	new = malloc(sizeof(t_command));
	new->argv = NULL;
	new->redirect = NULL;
	new->complete = 0;
	return (new);
}
