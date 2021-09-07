#include "libft.h"

void	proc_hex(t_option *options, va_list ap, char x)
{
	unsigned int	num;
	char			*number;

	num = va_arg(ap, int);
	if (options->precision == 0 && num == 0)
	{
		number = "";
		print_num(options, number);
	}
	else
	{
		number = ft_hex(num, x);
		if (number == NULL)
		{
			options->error = -1;
			return ;
		}
		print_num(options, number);
		free(number);
	}
}
