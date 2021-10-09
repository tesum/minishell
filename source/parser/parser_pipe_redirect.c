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
	char	*redirect;
	char	*tmp;

	*this_is_redirect = 1;
	if ((input[*i] == '<' && input[(*i + 1)] == '<') || \
		(input[*i] == '>' && input[(*i + 1)] == '>'))
	{
		redirect = ft_substr(input, *i, 2);
		*i += 2;
		tmp = other_handler(input, i);
		redirect = ft_strjoin_gnl(redirect, tmp);
		free(tmp);
		if (set_redirect(redirect, this_is_redirect) == 0)
			return (redirect);
	}
	if (*this_is_redirect == -1)
		error_malloc(redirect, NULL, NULL);
	return (redirect_handler(input, i, this_is_redirect));
}

char	*redirect_handler(char const *input, int *i, int *this_is_redirect)
{
	char	*redirect;
	char	*tmp;

	if ((input[*i] == '<' && *this_is_redirect != -1) || \
		(input[*i] == '>' && *this_is_redirect != -1))
	{
		redirect = ft_substr(input, *i, 1);
		*i += 1;
		tmp = other_handler(input, i);
		redirect = ft_strjoin_gnl(redirect, tmp);
		free(tmp);
		if (set_redirect(redirect, this_is_redirect) == 0)
			return (redirect);
	}
	if (*this_is_redirect == -1)
		error_malloc(tmp, NULL, NULL);
	return (NULL);
}

int	set_redirect(char *str, int *this_is_redirect)
{
	t_command	*tmp;
	t_list		*new;

	if (str == NULL)
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

char	**limiter_handler(char **str)
{
	char		*tmp;
	char		*name;
	int static	i = 0;
	int			fd;

	name = ft_itoa(i);
	i++;
	tmp = ft_strjoin(".tmp/", name);
	free(name);
	name = tmp;
	fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd < 0)
		exit_error("File discriptor error", -1);
	while(1)
	{
		tmp = readline("heredoc> ");
		if (!ft_strncmp(str[1], tmp, ft_strlen(str[1])))
			break ;
		ft_putendl_fd(tmp, fd);
		free(tmp);
	}
	close(fd);
	str[0][1] = '\0';
	free(str[1]);
	str[1] = name;
	return (str);
}
