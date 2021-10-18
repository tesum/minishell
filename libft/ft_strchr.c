/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsenijdrozdov <arsenijdrozdov@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 12:27:08 by arsenijdroz       #+#    #+#             */
/*   Updated: 2021/10/18 12:27:09 by arsenijdroz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int ch)
{
	size_t	i;
	char	*strfind;

	i = 0;
	strfind = (char *)str;
	while (strfind[i] != '\0')
	{
		if (strfind[i] == ch)
			return (strfind + i);
		i++;
	}
	if (ch == '\0')
		return (strfind + i);
	return (0);
}
