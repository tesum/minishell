/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caugusta <caugusta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 01:07:33 by demilan           #+#    #+#             */
/*   Updated: 2021/10/03 20:23:07 by caugusta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// parsing main
int	parsing(void)
{
	char	*input = "env";

	signal_handler();
	input = readline("minishell$ ");
	if (!input)
		return (-1);
	if (ft_strlen(input) == 0)
	{
		g_shell.result = 0;
		free(input);
		input = NULL;
		return (1);
	}
	add_history(input);
	if (preparser(input) != -1)
		parser(input);
	else
		return (1);
	free(input);
	return (0);
}
