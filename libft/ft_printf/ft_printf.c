#include "libft.h"

void	init_struct(t_option *options, int len)
{
	options->flag_minus = 0;
	options->flag_zero = 0;
	options->width = 0;
	options->dot = 0;
	options->precision = -1;
	options->count = len;
	options->type = 0;
	options->skip = 0;
	options->star_width = 0;
	options->star_precision = 0;
	options->error = 0;
}

void	if_just_dot(t_option *options)
{
	if (options->dot && options->precision == -1
		&& !options->star_precision)
	{
		options->precision = 0;
		options->skip += 1;
	}
}

int	ft_printf(const char *format, ...)
{
	va_list		ap;
	t_option	options;

	init_struct(&options, 0);
	va_start (ap, format);
	parse_input((char *)format, &options, ap);
	va_end(ap);
	return (options.count);
}
