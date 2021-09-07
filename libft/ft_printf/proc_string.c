#include "libft.h"

static void	print_s(t_option *options, char *str);
static void	print_s2(t_option *options, int i, char *str);

static void	print_s(t_option *options, char *str)
{
	int	i;

	i = 0;
	if (options->width > 0 && !options->flag_minus)
	{
		while (str[i] != '\0' && i < options->precision)
			i++;
		while (i < options->width)
		{
			if (!options->flag_zero)
				ft_putchar_fd(' ', 1);
			else
				ft_putchar_fd('0', 1);
			i++;
			options->count += 1;
		}
	}
	i = 0;
	print_s2(options, i, str);
}

static void	print_s2(t_option *options, int i, char *str)
{
	while (*str != '\0' && i < options->precision)
	{
		ft_putchar_fd(*str++, 1);
		options->count += 1;
		i++;
	}
	if (i < options->width && options->flag_minus)
	{
		while (i < options->width)
		{
			ft_putchar_fd(' ', 1);
			i++;
			options->count += 1;
		}
	}
}

void	proc_string(t_option *options, va_list ap)
{
	char	*str;

	if (options->precision < 0)
		options->precision = 2147483647;
	str = va_arg(ap, char *);
	if (str == NULL)
		str = "(null)";
	print_s(options, str);
}
