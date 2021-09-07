#include "libft.h"

void	pars_flags(char *parsing, t_option *options, va_list ap)
{
	int	i;

	i = 0;
	while (1)
	{
		if (parsing[i] == '-')
			options->flag_minus = 1;
		else if (parsing[i] == '0')
			options->flag_zero = 1;
		else
			break ;
		i++;
	}
	if (options->flag_minus == 1)
		options->flag_zero = 0;
	options->skip += i;
	pars_width(parsing + i, options, ap);
}

void	pars_width(char *parsing, t_option *options, va_list ap)
{
	int	i;

	i = 0;
	if (ft_isdigit((int)parsing[i]))
	{
		options->width = ft_atoi(parsing + i);
		while (ft_isdigit((int)parsing[i]))
			i++;
		options->skip += i;
	}
	else if (parsing[i] == '*')
	{
		options->star_width = 1;
		options->width = va_arg(ap, int);
		if (options->width < 0)
		{
			options->flag_minus = 1;
			options->flag_zero = 0;
			options->width = -options->width;
		}
		i++;
		options->skip += i;
	}
	pars_dot_precision(parsing + i, options, ap);
}

void	pars_dot_precision(char *parsing, t_option *options, va_list ap)
{
	int	i;

	i = 0;
	if (parsing[i] == '.')
	{
		options->dot = 1;
		i++;
		if (ft_isdigit((int)parsing[i]))
		{
			options->precision = ft_atoi(parsing + i);
			while (ft_isdigit((int)parsing[i]))
				i++;
			options->skip += i;
		}
		else if (parsing[i] == '*')
		{
			options->star_precision = 1;
			options->precision = va_arg(ap, int);
			i++;
			options->skip += i;
		}
		if (options->precision >= 0)
			options->flag_zero = 0;
	}
	pars_type(parsing + i, options, ap);
}

void	pars_type(char	*parsing, t_option *options, va_list ap)
{
	if_just_dot(options);
	if (*parsing == 'c')
		proc_char(options, ap);
	else if (*parsing == 's')
		proc_string(options, ap);
	else if (*parsing == 'p')
		proc_pointer(options, ap);
	else if (*parsing == 'd' || *parsing == 'i')
		proc_int(options, ap);
	else if (*parsing == 'u')
		proc_uint(options, ap);
	else if (*parsing == 'x')
		proc_hex(options, ap, 'x');
	else if (*parsing == 'X')
		proc_hex(options, ap, 'X');
	else if (*parsing == '%')
		proc_percent(options);
	else if (*parsing == 'n')
		proc_n(options, ap);
	else
		proc_notype(options);
	options->skip += 1;
}

void	parse_input(char *parsing, t_option *options, va_list ap)
{
	int	i;

	i = 0;
	while (parsing[i] != '\0')
	{
		while (parsing[i] != '\0' && parsing[i] != '%')
		{
			ft_putchar_fd(parsing[i], 1);
			i++;
			options->count += 1;
		}
		if (parsing[i] == '%')
		{
			pars_flags(parsing + ++i, options, ap);
			i += options->skip;
		}
		if (options->error == -1)
			return ;
		init_struct(options, options->count);
	}
}
