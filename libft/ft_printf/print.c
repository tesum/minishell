#include "libft.h"

void	print_num(t_option *options, char *number)
{
	options->width -= ft_strlen(number);
	options->precision -= ft_strlen(number);
	if (number[0] == '-')
		options->precision += 1;
	if (!options->flag_zero && !options->flag_minus)
	{
		while (options->width > 0 && options->width > options->precision)
		{
			ft_putchar_fd(' ', 1);
			options->count += 1;
			options->width -= 1;
		}
	}
	if (number[0] == '-')
	{
		ft_putchar_fd('-', 1);
		options->count += 1;
		number++;
	}
	print_num2(options, number);
}

void	print_num2(t_option *options, char *number)
{
	if (options->precision > 0 && !options->flag_zero && options->width
		> options->precision)
	{
		while (options->width > 0 && options->precision > 0)
		{
			ft_putchar_fd('0', 1);
			options->count += 1;
			options->precision -= 1;
			options->width -= 1;
		}
	}
	else if ((options->precision > 0 && !options->flag_zero)
		|| options->width < options->precision)
	{
		while (options->precision > 0)
		{
			ft_putchar_fd('0', 1);
			options->count += 1;
			options->precision -= 1;
			options->width -= 1;
		}
	}
	print_num3(options, number);
}

void	print_num3(t_option *options, char *number)
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
