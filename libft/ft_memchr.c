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
