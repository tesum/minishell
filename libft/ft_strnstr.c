#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	len2;

	i = 0;
	len2 = ft_strlen(needle);
	if (len2 == 0)
		return ((char *)haystack);
	while (i < len && (char)haystack[i] != '\0')
	{
		if (haystack[i] == needle[0])
		{
			if (ft_strncmp(haystack + i, needle, len2) == 0)
				if (i + len2 <= len)
					return ((char *)haystack + i);
		}
		i++;
	}
	return (0);
}
