#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list		*new;

	if (content == NULL)
		return (NULL);
	new = malloc(sizeof(t_list));
	if (new == NULL)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}
