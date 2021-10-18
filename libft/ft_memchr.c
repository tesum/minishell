/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsenijdrozdov <arsenijdrozdov@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 12:26:45 by arsenijdroz       #+#    #+#             */
/*   Updated: 2021/10/18 12:26:46 by arsenijdroz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t len)
{
	unsigned char	*strc;

	strc = (unsigned char *)str;
	while (len > 0)
	{
		if (*strc == (unsigned char)c)
			return ((unsigned char *)strc);
		strc++;
		len--;
	}
	return (0);
}
