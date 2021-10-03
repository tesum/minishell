#include "minishell.h"

static	int	check_arg(char *arg)
{
	int	i;
	int	r;

	i = 0;
	r = 0;
	if (arg[i] == '=')
		return (1);
	while (arg[i])
	{
		if (arg[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

void	del_env_line(t_env *env, char *key)
{
	t_env	*tmp;
	t_env	*tmp_del;

	tmp_del = find_list_env(env, key);
	tmp = env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->next->key, key, ft_strlen(key)))
			break ;
		tmp = tmp->next;
	}
	tmp->next = tmp_del->next;
	free(tmp_del->key);
	free(tmp_del->value);
	tmp_del->next = NULL;
	free(tmp_del);
	tmp_del = NULL;
}

void	ft_unset(char **argv)
{
	int	i;

	i = 1;
	if (argv[1])
	{
		while (argv[i])
		{
			if (check_arg(argv[i]))
			{
				ft_putstr_fd("unset: Invalid parameter name\n", 2);
				return ;
			}
			else
				del_env_line(g_shell.new_env, argv[i]);
			i++;
		}
	}
	return ;
}
