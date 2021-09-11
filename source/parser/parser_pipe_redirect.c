#include "minishell.h"

int		pipe_handler(int *i)
{
	t_command *new;
	t_list *new_list;
	*i += 1;

	new = command_new();
	if (new == NULL)
		return (-1);
	new_list = ft_lstnew((void *)new);
	if (new_list == NULL)
	{
		free(new);
		return (-1);
	}
	ft_lstadd_back(&g_shell.cmd, (void *)new_list);
	return (0);
}

char	*double_redirect_handler(char const *input, int *i, int *this_is_redirect)
{
	char	**tmp_str;

	tmp_str = malloc(sizeof(char *) * 3);
	*this_is_redirect = 1;
	if (input[*i] == '<' && input[(*i + 1)] == '<')
	{
		tmp_str[0] = ft_substr(input, *i, 2);
		*i += 2;
		tmp_str[1] = other_handler(input, i);
		tmp_str[2] = NULL;
		if (set_redirect(tmp_str, this_is_redirect) == 0)
			return (tmp_str[0]);
	}
	else if (input[*i] == '>' && input[(*i + 1)] == '>')
	{
		tmp_str[0] = ft_substr(input, *i, 2);
		*i += 2;
		tmp_str[1] = other_handler(input, i);
		tmp_str[2] = NULL;
		if (set_redirect(tmp_str, this_is_redirect) == 0)
			return (tmp_str[0]);
	}
	if (*this_is_redirect == -1)
		error_malloc(tmp_str[0], tmp_str[1], NULL);
	return (redirect_handler(input, i, this_is_redirect));
}

char	*redirect_handler(char const *input, int *i, int *this_is_redirect)
{
	char	**tmp_str;

	tmp_str = malloc(sizeof(char *) * 3);
	if (input[*i] == '<' && *this_is_redirect != -1)
	{
		tmp_str[0] = ft_substr(input, *i, 1);
		*i += 1;
		tmp_str[1] = other_handler(input, i);
		tmp_str[2] = NULL;
		if (set_redirect(tmp_str, this_is_redirect) == 0)
			return (tmp_str[0]);
	}
	else if (input[*i] == '>' && *this_is_redirect != -1)
	{
		tmp_str[0] = ft_substr(input, *i, 1);
		*i += 1;
		tmp_str[1] = other_handler(input, i);
		tmp_str[2] = NULL;
		if (set_redirect(tmp_str, this_is_redirect) == 0)
			return (tmp_str[0]);
	}
	if (*this_is_redirect == -1)
		error_malloc(tmp_str[0], tmp_str[1], NULL);
	return (NULL);
}

int	set_redirect(char **str, int *this_is_redirect)
{
	t_command	*tmp;
	t_list		*new;

	if (str[0] == NULL || str[1] == NULL)
	{
		*this_is_redirect = -1;
		return (-1);
	}
	tmp = (t_command *)ft_lstlast(g_shell.cmd)->content;
	new = ft_lstnew((void *)str);
	if (new == NULL)
	{
		*this_is_redirect = -1;
		return (-1);
	}
	ft_lstadd_back(&tmp->redirect, new);
	return (0);
}