#include "libft.h"

void	*ft_bzero(void *dst, size_t len)
{
	unsigned char	*bz;

	bz = ft_memset(dst, 0, len);
	return (bz);
}
