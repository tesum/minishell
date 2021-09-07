#include "libft.h"

int	ft_memcmp(const void *str1, const void *str2, size_t len)
{
	unsigned char		*strc1;
	unsigned char		*strc2;

	strc1 = (unsigned char *)str1;
	strc2 = (unsigned char *)str2;
	while (len-- > 0)
	{
		if (*strc1 != *strc2 || !strc1 || !strc2)
			return (*strc1 - *strc2);
		strc1++;
		strc2++;
	}
	return (0);
}
