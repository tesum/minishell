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
	if (!ft_strncmp(str[0], "<<", 3))
	{

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
