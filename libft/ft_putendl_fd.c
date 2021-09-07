#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	size_t	i;

	if (s == NULL)
		return ;
	i = 0;
	while (s[i++] != '\0')
		ft_putchar_fd(s[i - 1], fd);
	ft_putchar_fd('\n', fd);
}
