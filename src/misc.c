#include <stdio.h>
#include "push_swap.h"

static void	maximizing_result(t_list *a, const t_list *push_candidate, t_list **tmp)
{
	t_content	*candidate_content;

	candidate_content = CONTENT_OF_ELEMENT(push_candidate);
	if (CONTENT_OF_ELEMENT(a)->i <= candidate_content->i
		&& (! *tmp
			|| CONTENT_OF_ELEMENT(a)->i > CONTENT_OF_ELEMENT(*tmp)->i))
		*tmp = a;
}

static void	minimizing_result(t_list *a, const t_list *push_candidate, t_list **tmp)
{
	t_content	*candidate_content;

	candidate_content = CONTENT_OF_ELEMENT(push_candidate);
	if (CONTENT_OF_ELEMENT(a)->i >= candidate_content->i
		&& (! *tmp
			|| CONTENT_OF_ELEMENT(a)->i < CONTENT_OF_ELEMENT(*tmp)->i))
		*tmp = a;
}

static t_list	*get_element_which_is(t_list *a, t_list *push_candidate, \
void (*element_comparison)(t_list *a, const t_list *candidate, t_list **result))
{
	t_list		*result;

	if (! push_candidate)
		return (NULL);
	result = NULL;
	while (a)
	{
		element_comparison(a, push_candidate, &result);
		a = a->next;
	}
	return (result);
}

t_list	*get_biggest_element_smaller_than_candidate(t_list *a, t_list *push_candidate)
{
	return (get_element_which_is(a, push_candidate, maximizing_result));
}

t_list	*get_smallest_element_bigger_than_candidate(t_list *a, t_list *push_candidate)
{
	return (get_element_which_is(a, push_candidate, minimizing_result));
}
