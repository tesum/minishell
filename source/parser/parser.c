#include "minishell.h"

void	parser(char const *input)
{
	int		i;
	int		this_is_redirect;
	char	*tmp;

	i = 0;
	this_is_redirect = 0;
	while (input[i] && input[i] != '|')
	{
		while (ft_isspace(input[i]))
			i++;
		if (input[i] == '<' || input[i] == '>')
			tmp = double_redirect_handler(input, &i, &this_is_redirect);
		else if (input[i] == '|')
		{
			if (pipe_handler(&i) == -1)
				return ;
			continue ;
		}
		else
			tmp = other_handler(input, &i);
		if (set_arg(tmp, &this_is_redirect) == -1 && tmp != NULL)
			free(tmp);
	}
}

int	set_arg(char *str, int *this_is_redirect)
{
	t_command	*tmp;
	t_list		*new;

	if (str == NULL)
	{
		g_shell.error_malloc = 1;
		return (-1);
	}
	if (*this_is_redirect == 1)
	{
		*this_is_redirect = 0;
		return (0);
	}
	if (ft_strlen(str) == 0)
		return (-1);
	tmp = (t_command *)ft_lstlast(g_shell.cmd)->content;
	new = ft_lstnew((void *)str);
	if (new == NULL)
	{
		g_shell.error_malloc = 1;
		return (-1);
	}
	ft_lstadd_back(&tmp->argv, new);
	return (0);
}

char	*quote_handler(char const *input, int quote, int *i)
{
	int		j;
	char	*tmp_str;

	j = ++(*i);
	while (input[*i] != quote && input[*i] != '\0')
		(*i)++;
	tmp_str = ft_substr(input, j, *i - j);
	if (quote == 34)
	{
		j = 0;
		while(tmp_str != NULL && tmp_str[j])
		{
			if (tmp_str != NULL && tmp_str[j] == '$')
				tmp_str = dollar(tmp_str, &j);
			else
				j++;
		}
	}
	(*i)++;
	return (tmp_str);
}

char	*other_handler(char const *input, int *i)
{
	int		j;
	char	*tmp;

	if (input[*i] == '\0')
		return (ft_strdup(""));
	while (ft_isspace(input[*i]))
		(*i)++;
	j = *i;
	if (input[*i] == '\'' || input[*i] == '\"')
		return (quote_handler(input, input[*i], i));
	while (input[*i] != '<' && input[*i] != '>' && input[*i] != '|' && \
		!ft_isspace(input[*i]) && input[*i])
		(*i)++;
	tmp = ft_substr(input, j, *i - j);
	j = 0;
	if (tmp != NULL && tmp[j] == '$')
		tmp = dollar(tmp, &j);
	return (tmp);
}

void	error_malloc(char *a, char *b, char *c)
{
	if (a != NULL)
	{
		free(a);
		a = NULL;
	}
	if (b != NULL)
	{
		free(b);
		b = NULL;
	}
	if (c != NULL)
	{
		free(c);
		c = NULL;
	}
	g_shell.result = -1;
	ft_putstr_fd("Error malloc", 2);
}
