#include "minishell.h"

int		export_sort(char **exp)
{
	int	i;

	i = 0;
	while (exp[i + 1])
	{
		if (exp[i][0] > exp[i + 1][0])
			return (1);
		i++;
	}
	return (0);
}

char	**sort_export(char **exp)
{
	int	i	;
	char	*tmp;

	while (1)
	{
		if (!export_sort(exp))
			break ;
		i = 0;
		while (exp[i + 1] != '\0')
		{
			if (exp[i][0] < exp[i + 1][0])
				i++;
			else
			{
				tmp = exp[i];
				exp[i] = exp[i + 1];
				exp[i + 1] = tmp;
				i++;
			}
		}
	}

	return (exp);
}

static	int	check_arg(char *arg, char ***env)
{
	int	i;

	i = 0;
	if (arg[i] == '=')
		return (0);
	while(arg[i])
	{
		printf("%c\n", arg[i]);
		if (arg[i] == '=' && arg[i + 1] == '=')
		{
			ft_putstr_fd("export: not found\n", 2);
			return (0);
		}
		if (arg[i] == '=')
		{
			*env = arr_add_back(*env, arg);
			return (1);
		}
		i++;
	}
	return (0);
}

void	put_export(void)
{
	// char	**new;
	char	**exp;
	int		size;
	int		i;
	// int		j;

	exp = sort_export(g_shell.env);
	size = arr_size(exp);
	// new = malloc(sizeof(char *) * (size + 1));
	// i = -1;
	// j = 0;
	// while (exp[++i])
	// {
	// 	new[j] = ft_strjoin("declare -x ", exp[i]);
	// 	j++;
	// }
	// new[j] = NULL;
	// free(new);


	i = 0;
	while (exp[i])
	{
		// printf("%s\n",exp[i]);
		ft_putstr_fd(ft_strjoin(exp[i], "\n"), STDOUT_FILENO);
		i++;
	}
}


// если есть такой же аргумент - заменяется только значение
// zsh or bash?
void	ft_export(char **argv)
{
	int	i;

	i = 1;
	if (argv[1])
	{
		while (argv[i])
		{
			if (check_arg(argv[i], &g_shell.env));
				// put_export();
			else
			{
				return ;
			}
			i++;
		}
		
	}
	else
		put_export();
	return ;
}
