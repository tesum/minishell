#include "libft.h"

void	proc_uint(t_option *options, va_list ap)
{
	unsigned long	num;
	char			*number;

	num = va_arg(ap, unsigned int);
	if (options->precision == 0 && num == 0)
	{
		number = "";
		print_num(options, number);
	}
	else
	{
		number = ft_utoa(num);
		if (number == NULL)
		{
			options->error = -1;
			return ;
		}
		print_num(options, number);
		free(number);
	}
}
