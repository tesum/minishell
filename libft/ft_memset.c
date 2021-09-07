#include "libft.h"

void	*ft_memset(void *dst, int c, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
		*((unsigned char *)dst + i++) = (unsigned char)c;
	return (dst);
}
