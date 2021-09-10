#include "minishell.h"

void	command_add_back(t_command **lst, t_command *new)
{
	t_command	*last;

	if (lst == NULL || new == NULL)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		last = command_last(*lst);
		(last)->next = new;
	}
}

void	command_add_front(t_command **lst, t_command *new)
{
	t_command	*first;

	first = new;
	first->next = *lst;
	*lst = first;
}

t_command	*command_last(t_command *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

t_command	*command_new(char	**formated)
{
	t_command		*new;
	int				i;

	i = 0;
	new = malloc(sizeof(t_command));
	if (new == NULL)
		return (NULL);
	while (formated[i] && formated[i][0] != '|')
	{
		printf("\033[0;32mformated is %s\n\033[0m", formated[i]);
		if (formated[i][0] == '<' || formated[i][0] == '>')
		{
			printf("\033[0;31mredir\n");
			new->redirect = arr_add_back(new->redirect, formated[i]);
			printf("r = %s\n", new->redirect[0]);
			new->redirect = arr_add_back(new->redirect, formated[i + 1]);
			printf("\033[0m");
			if (new->redirect == NULL)
			{
				free(new);
				return (NULL);
			}
			i += 2;
		}
		else if (formated[i][0] != '|')
		{
			printf("cmd = %s\n", formated[i]);
			new->argv = arr_add_back(new->argv, formated[i]);
			printf("add back\n");
			if (new->argv == NULL)
			{
				// структура полностью чистится же
				// free_2d_arr(new->redirect);
				printf("clear\n");
				free(new);
				return (NULL);
			}
			i++;
		}
		else
			i++;
	}
	new->next = NULL;
	printf("new cmd\n");
	return (new);
}

int	command_size(t_command *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}
