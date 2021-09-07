#include "libft.h"

void	proc_int(t_option *options, va_list ap)
{
	int		num;
	char	*number;

	num = va_arg(ap, int);
	if (options->precision == 0 && num == 0)
	{
		number = "";
		print_num(options, number);
	}
	else
	{
		number = ft_itoa(num);
		if (number == NULL)
		{
			options->error = -1;
			return ;
		}
		print_num(options, number);
		free(number);
	}
}

void	proc_n(t_option *options, va_list ap)
{
	int	*p;

	p = va_arg(ap, int *);
	*p = options->count;
}
