#include "libft.h"

static void	print_s(t_option *options, char str);
static void	print_s2(t_option *options, char str);

static void	print_s(t_option *options, char str)
{
	options->width -= 1;
	if (!options->flag_zero && !options->flag_minus)
	{
		while (options->width > 0)
		{
			ft_putchar_fd(' ', 1);
			options->count += 1;
			options->width -= 1;
		}
	}
	if (options->flag_zero && !options->flag_minus)
	{
		while (options->width > 0)
		{
			ft_putchar_fd('0', 1);
			options->count += 1;
			options->width -= 1;
		}
	}
	print_s2(options, str);
}

static void	print_s2(t_option *options, char str)
{
	ft_putchar_fd(str, 1);
	options->count += 1;
	if (options->width > 0 && options->flag_minus)
	{
		while (options->width > 0)
		{
			ft_putchar_fd(' ', 1);
			options->count += 1;
			options->width -= 1;
		}
	}
}

void	proc_percent(t_option *options)
{
	char	out;

	out = '%';
	print_s(options, out);
}

void	proc_notype(t_option *options)
{
	write (1, "%", 1);
	options->skip = 0;
}
