#include "libft.h"

static void	print_point(t_option *options, char *number);
static void	print_point2(t_option *options, char *number);
static void	print_point3(t_option *options, char *number);

static void	print_point(t_option *options, char *number)
{
	options->width = options->width - ft_strlen(number) - 2;
	options->precision -= ft_strlen(number);
	if (!options->flag_zero && !options->flag_minus)
	{
		while (options->width > 0 && options->width > options->precision)
		{
			ft_putchar_fd(' ', 1);
			options->count += 1;
			options->width -= 1;
		}
	}
	ft_putchar_fd('0', 1);
	ft_putchar_fd('x', 1);
	options->count += 2;
	print_point2(options, number);
}

static void	print_point2(t_option *options, char *number)
{
	if (options->precision > 0 && options->width > 0 && !options->flag_zero)
	{
		while (options->width > 0 && options->precision > 0)
		{
			ft_putchar_fd('0', 1);
			options->count += 1;
			options->precision -= 1;
			options->width -= 1;
		}
	}
	else if (options->precision > 0 && !options->flag_zero)
	{
		while (options->precision > 0)
		{
			ft_putchar_fd('0', 1);
			options->count += 1;
			options->precision -= 1;
			options->width -= 1;
		}
	}
	print_point3(options, number);
}

static void	print_point3(t_option *options, char *number)
{
	if (options->flag_zero)
	{
		while (options->width > 0)
		{
			ft_putchar_fd('0', 1);
			options->count += 1;
			options->width -= 1;
		}
	}
	while (*number != '\0')
	{
		ft_putchar_fd(*number, 1);
		number++;
		options->count += 1;
	}
	if (options->flag_minus)
	{
		while (options->width > 0)
		{
			ft_putchar_fd(' ', 1);
			options->count += 1;
			options->width -= 1;
		}
	}
}

void	proc_pointer(t_option *options, va_list ap)
{
	unsigned long		num;
	char				*number;

	num = va_arg(ap, unsigned long);
	if (options->precision == 0 && num == 0)
	{
		number = "";
		print_point(options, number);
	}
	else
	{
		number = ft_ultimate_hex(num, 'x');
		if (number == NULL)
		{
			options->error = -1;
			return ;
		}
		print_point(options, number);
		free(number);
	}
}
