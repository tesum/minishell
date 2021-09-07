#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	t_list	*first;

	first = new;
	first->next = *lst;
	*lst = first;
}
