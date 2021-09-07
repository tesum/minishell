#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*arr;

	arr = malloc(count * size);
	if (arr == NULL)
		return (NULL);
	arr = ft_bzero(arr, count * size);
	return (arr);
}
