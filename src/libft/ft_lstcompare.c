#include "libft.h"

int	ft_lstcompare(t_list *a, t_list *b, int (*compare)(void *, void *))
{
	if (! a || !b)
		return (0);
	while (a && b)
	{
		if (! compare(a->content, b->content))
			return (0);
		a = a->next;
		b = b->next;
	}
	if (a || b)
		return (0);
	return (1);
}
