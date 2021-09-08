#include "minishell.h"

char	*dollar(char *input, char **env, int *i)
{
	int		j;
	int		k;
	char	*tmp;
	char	*tmp2;

	j = 0;
	k = ++*i;
	if (dollar_utils(input, i, &k) != NULL)
		return (input);
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
	return (replace_variable(input, "", i, k));
}

char	*dollar_utils(char *input, int *i, int *k)
{
	if (ft_isdigit(input[*k]) == 1 && ft_isdigit(input[(*k) + 1]) == 1)
		(*k)++;
	else
	{
		while (input[*k])
		{
			if (input[*k] == '_' || ft_isalnum((int)input[*k]) == 1)
				(*k)++;
			else
				break ;
		}
		if (*k == *i)
			return (input);
	}
	return (NULL);
}

char	*replace_variable(char *input, char *str_replace, int *start, int end)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = ft_substr(input, 0, *start - 1);
	tmp2 = ft_strdup(input + end);
	if (tmp1 == NULL || tmp2 == NULL)
	{
		error_malloc(tmp1, tmp2, input);
		return (NULL);
	}
	free(input);
	end = 0;
	while (str_replace[end - 1] != '=')
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
