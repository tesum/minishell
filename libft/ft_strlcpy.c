#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	if (dst == NULL)
		return (0);
	i = 0;
	if (size < 1)
		return (ft_strlen(src));
	while (i < size - 1 && ft_strlen(src) > i)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}
