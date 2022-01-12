#include "push_swap.h"

int	ascending_order(void *in, void *comp)
{
	return (((t_content *)in)->i <= ((t_content *)comp)->i);
}

void	do_not_free_content(void *content)
{
	(void) content;
}

void	*shallow_copy(void *content)
{
	return (content);
}

void	index_stack(t_list *stack)
{
	t_list	*cpy;
	t_list	*cpy_start;
	int		index;

	index = 0;
	cpy = ft_lstmap(stack, shallow_copy, free);
	cpy_start = cpy;
	ft_lstsort(&cpy, ascending_order);
	while (cpy)
	{
		((t_content *) cpy->content)->index = index++;
		cpy = cpy->next;
	}
	ft_lstclear(&cpy_start, do_not_free_content);
}
