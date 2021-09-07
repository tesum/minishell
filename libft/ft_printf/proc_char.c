#include "libft.h"

static void	print_s(t_option *options, char str);
static void	print_s2(t_option *options, char str);

static void	print_s(t_option *options, char str)
{
	int	i;

	i = 0;
	if (options->width > 0 && !options->flag_minus)
	{
		while (i < options->width - 1)
		{
			ft_putchar_fd(' ', 1);
			i++;
			options->count += 1;
		}
	}
	print_s2(options, str);
}

static void	print_s2(t_option *options, char str)
{
	int	i;

	i = 0;
	ft_putchar_fd(str, 1);
	options->count += 1;
	if (i < options->width - 1 && options->flag_minus)
	{
		while (i < options->width - 1)
		{
			ft_putchar_fd(' ', 1);
			i++;
			options->count += 1;
		}
	}
}

void	proc_char(t_option *options, va_list ap)
{
	char	out;

	out = va_arg(ap, int);
	print_s(options, out);
}
