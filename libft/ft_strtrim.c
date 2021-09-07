#include "libft.h"

static int	cmp_ca(char c, char *arr)
{
	while (*arr != '\0')
	{
		if (*arr == c)
			return (1);
		arr++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	len;

	if (s1 == NULL || set == NULL)
		return (NULL);
	while (cmp_ca(*s1, (char *)set) == 1)
		s1++;
	if (*s1 == '\0')
		return (ft_strdup(""));
	len = ft_strlen(s1) - 1;
	while (cmp_ca(s1[len], (char *)set) == 1)
		len--;
	return (ft_substr(s1, 0, len + 1));
}
