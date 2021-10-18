/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsenijdrozdov <arsenijdrozdov@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 12:27:33 by arsenijdroz       #+#    #+#             */
/*   Updated: 2021/10/18 12:27:34 by arsenijdroz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, size_t start, size_t len)
{
	char	*sub;
	size_t	i;

	if (s == NULL)
		return (NULL);
	i = 0;
	if (ft_strlen(s) <= start)
		return (ft_strdup(""));
	while (start > 0 && *s != '\0')
	{
		s++;
		start--;
	}
	sub = (char *)malloc(sizeof(char) * (len + 1));
	if (sub == NULL)
		return (NULL);
	while (len > 0 && s[i] != '\0')
	{
		sub[i] = s[i];
		i++;
		len--;
	}
	sub[i] = '\0';
	return (sub);
}
