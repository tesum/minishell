#include "minishell.h"

void	parser(char *input, char **env)
{
	int	i;
	char	**formated;

	i = -1;
	while (input != NULL && input[++i])
	{
		if (input != NULL && input[i] == '\'')
			input = single_quote(input, &i);
		if (input != NULL && input[i] == '\\')
		{
			input = delete_simbol(input, i);
			i++;
		}
		if (input != NULL && input[i] == '\"')
			input = double_quote(input, env, &i);
		if (input != NULL && input[i] == '$')
			input = dollar(input, env, &i);
		if (input != NULL && (input[i] == ' ' || input[i] == '\t'))
			input[i] = 127;
	}
	printf("str = %s\n", input);
	formated = ft_split(input, 127);
	i = -1;
	while (formated[++i])
		printf("[%d] - %s\n", i, formated[i]);
	free (input);
}

char	*double_quote(char *input, char **env, int *i)
{
	input = delete_simbol(input, *i);
	if (input == NULL)
		return (NULL);
	while (input[*i] != '\"')
	{
		if (input != NULL && input[*i] == '$')
		{
			input = dollar(input, env, i);
			if (input == NULL)
				return (NULL);
		}
		else
			(*i)++;
	}
	input = delete_simbol(input, *i);
	if (input == NULL)
		return (NULL);
	return (input);
}

char	*dollar(char *input, char **env, int *i) //TODO: norm 37line
{
	int	j;
	int	k;
	char *tmp;
	char *tmp2;

	j = 0;
	k = ++*i;
	if (ft_isdigit(input[k]) == 1 && ft_isdigit(input[k + 1]) == 1)
		k++;
	else
	{
		while (input[k])
		{
			if (input[k] == '_' || ft_isalnum((int)input[k]) == 1)
				k++;
			else
				break ;
		}
		if (k == *i)
			return (input);
	}
	tmp = ft_substr(input, *i, k - *i);
	tmp = ft_strjoin_gnl(tmp, "=");
	if (tmp == NULL)
		error_malloc(tmp, input, NULL);
	while (env[j])
	{
		tmp2 = ft_strnstr(env[j], tmp, ft_strlen(tmp));
		if (tmp2 != NULL)
		{
			free(tmp);
			return (replace_variable(input, tmp2, i, k));
		}
		j++;
	}
	free(tmp);
	return(replace_variable(input, "", i, k));
}

char	*replace_variable(char *input, char *str_replace, int *start, int end)
{
	char	*tmp1;
	char	*tmp2;
	tmp1 = ft_substr(input, 0, *start - 1);
	tmp2 = ft_strdup(input + end);
	if (tmp1 == NULL ||tmp2 == NULL)
	{
		error_malloc(tmp1, tmp2, input);
		return (NULL);
	}
	free(input);
	end = 0;
	while(str_replace[end - 1] != '=')
		end++;
	tmp1 = ft_strjoin_gnl(tmp1, str_replace + end);
	tmp1 = ft_strjoin_gnl(tmp1, tmp2);
	if (tmp1 == NULL)
	{
		error_malloc(tmp1, tmp2, input);
		return (NULL);
	}
	free (tmp2);
	*start += ft_strlen(str_replace + end) - 1;
	input = tmp1;
	return (input);
}

char	*single_quote(char *input, int *i)
{
	input = delete_simbol(input, *i);
	if (input == NULL)
		return (NULL);
	while (input[*i] != '\'')
		(*i)++;
	input = delete_simbol(input, *i);
	if (input == NULL)
		return (NULL);
	return (input);
}

char	*delete_simbol(char *input, int i)
{
	char	*tmp1;
	char	*tmp2;

	input[i] = '\0';
	tmp1 = ft_strdup(input);
	tmp2 = ft_strdup(input + i + 1);
	if (tmp1 == NULL || tmp2 == NULL)
	{
		error_malloc(tmp1, tmp2, input);
		return (NULL);
	}
	free(input);
	input = ft_strjoin(tmp1, tmp2);
	if (input == NULL)
	{
		error_malloc(tmp1, tmp2, input);
		return (NULL);
	}
	free (tmp1);
	free (tmp2);
	return (input);
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
	ft_putstr_fd("Error malloc", 2);
}
