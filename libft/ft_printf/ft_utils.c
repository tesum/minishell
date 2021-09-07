#include "libft.h"

static int	lennbr(int n)
{
	int		i;

	i = 1;
	if (n < 0)
	{
		n = -n;
		i++;
	}
	while (n / 10 > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_utoa(unsigned int n)
{
	char	*arr;
	int		i;

	i = lennbr((int)n);
	arr = (char *)malloc(sizeof(char) * (i + 1));
	if (arr == NULL)
		return (NULL);
	arr[i--] = '\0';
	while (n / 10 > 0)
	{
		arr[i] = (n % 10) + '0';
		n /= 10;
		i--;
	}
	arr[i] = (n % 10) + '0';
	return (arr);
}

void	reverse(char *s)
{
	int	ibegin;
	int	iend;
	int	c;

	ibegin = 0;
	iend = ft_strlen(s);
	if (iend == 1)
		return ;
	while (ibegin < iend)
	{
		c = s[ibegin];
		s[ibegin++] = s[--iend];
		s[iend] = c;
	}
}

char	*ft_hex(unsigned int num, char x)
{
	int				i;
	int				tmp;
	char			hex[100];

	i = 0;
	if (num == 0)
		hex[i++] = '0';
	while (num != 0)
	{
		tmp = num % 16;
		if (tmp < 10)
			tmp = tmp + 48;
		else if (x == 'X')
			tmp = tmp + 55;
		else
			tmp = tmp + 87;
		hex[i++] = tmp;
		num = num / 16;
	}
	hex[i] = '\0';
	reverse(hex);
	return (ft_strdup(hex));
}

char	*ft_ultimate_hex(unsigned long long num, char x)
{
	int				i;
	int				tmp;
	char			hex[100];

	i = 0;
	if (num == 0)
		hex[i++] = '0';
	while (num != 0)
	{
		tmp = num % 16;
		if (tmp < 10)
			tmp = tmp + 48;
		else if (x == 'X')
			tmp = tmp + 55;
		else
			tmp = tmp + 87;
		hex[i++] = tmp;
		num = num / 16;
	}
	hex[i] = '\0';
	reverse(hex);
	return (ft_strdup(hex));
}
