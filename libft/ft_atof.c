/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsenijdrozdov <arsenijdrozdov@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 12:25:44 by arsenijdroz       #+#    #+#             */
/*   Updated: 2021/10/18 12:25:45 by arsenijdroz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static double	ft_atof2(char **line, int i);

double	ft_atof(char **line)
{
	double	n;
	int		i;
	double	j;
	int		m;

	i = 0;
	n = 0.0;
	j = 0;
	m = 1;
	while ((line[0][i] >= 9 && line[0][i] <= 13) || line[0][i] == ' ')
		i++;
	if (line[0][i] == '-' || line[0][i] == '+')
	{
		if (line[0][i] == '-')
			m = -m;
		i++;
	}
	while (line[0][i] >= '0' && line[0][i] <= '9')
	{
		j = (j * 10) + (line[0][i] - '0');
		i++;
	}
	n = ft_atof2(line, i);
	return ((j + n) * m);
}

static double	ft_atof2(char **line, int i)
{
	double	n;
	int		j;
	int		k;

	n = 0;
	k = 10;
	if (line[0][i] == '.')
	{
		i++;
		j = i;
		while (line[0][i] >= '0' && line[0][i] <= '9')
		{
			n = n + ((double)(line[0][i] - '0') / k);
			k *= 10;
			i++;
		}
		if (j == i)
			n = 0.0;
	}
	else
		n = 0.0;
	return (n);
}
