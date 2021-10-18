/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demilan <demilan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 01:07:33 by demilan           #+#    #+#             */
/*   Updated: 2021/10/18 13:15:34 by demilan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// utils env
void	edit_env_line(t_env *env, char *find, char *edit)
{
	t_env	*tmp;

	tmp = find_list_env(env, find);
	if (tmp == NULL)
	{
		tmp = new_env(find, 0, 1);
		if (tmp == NULL)
			exit_error("Error Malloc", -1);
		add_back_env(&env, tmp);
	}
	if (edit)
	{
		tmp->env = 1;
		try_free(tmp->value);
		tmp->value = NULL;
		tmp->value = ft_strdup(edit);
	}
}

char	**env_arr(t_env *new_env, int export)
{
	char	**env;
	int		i;
	int		j;

	i = env_size(new_env);
	env = malloc(sizeof(char *) * (i + 1));
	if (env == NULL)
		exit_error("Error malloc", -1);
	j = 0;
	env[i] = NULL;
	while (j < i)
	{
		if ((export && new_env->exp) || !export)
		{
			env[j] = ft_strjoin_gnl(ft_strdup(""), new_env->key);
			if (new_env->env)
				env[j] = ft_strjoin_gnl(ft_strjoin_gnl(env[j], "="), \
					new_env->value);
			if (env[j] == NULL)
				exit_error("Error malloc", -1);
		}
		j++;
		new_env = new_env->next;
	}
	return (env);
}

void	status_handler(void)
{
	if (WIFEXITED(g_shell.result))
		g_shell.result = WEXITSTATUS(g_shell.result);
	else if (WIFSIGNALED(g_shell.result))
	{
		g_shell.result = 128 + WTERMSIG(g_shell.result);
		ft_putchar_fd('\r', 2);
	}
}

int	try_dup(int fd)
{
	int	dupp;

	dupp = dup(fd);
	if (dupp == -1)
		exit_error(strerror(errno), 1);
	return (dupp);
}

int	try_dup2(int fd, int fd2)
{
	int	dupp;

	dupp = dup2(fd, fd2);
	if (dupp == -1)
		exit_error(strerror(errno), 1);
	return (dupp);
}
