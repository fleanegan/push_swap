#include <stdio.h>
#include "push_swap.h"

int	is_element_fitter_than_old_candidate(int markup_count, \
enum markup_mode mode, t_list *old_candidate, t_list *new_candidate)
{
	static int		global_max_markup_count = 0;
	if (markup_count > global_max_markup_count ||
		(markup_count == global_max_markup_count &&
		 CONTENT_OF_ELEMENT(old_candidate)->index > \
		CONTENT_OF_ELEMENT(new_candidate)->index))
	{
		global_max_markup_count = markup_count;
		return (1);
	}
	return (0);
	(void) mode;
}
// 	printf("curr cand :%d, contester: %d, curr count: %d, contester count: %d\n",
//		   CONTENT_OF_ELEMENT(old_candidate)->i, CONTENT_OF_ELEMENT(new_candidate)->i, global_max_markup_count, markup_count);

t_list *calc_markup_reference(t_meta_stack *meta_stack, enum markup_mode mode)
{
	t_list	*first_element;
	t_list	*candidate;
	int		markup_count;
	int		is_at_start;

	is_at_start = 0;
	candidate = meta_stack->stack;
	first_element = meta_stack->stack;
	close_stack_ring(meta_stack->stack, meta_stack->last);
	while (! is_at_start)
	{
		markup_all_elements_according_to_reference(meta_stack, meta_stack->stack);
		markup_count = count_markups(meta_stack->stack);
		if (is_element_fitter_than_old_candidate(markup_count, mode, candidate, meta_stack->stack))
			candidate = meta_stack->stack;
		rotate(meta_stack, NULL);
		is_at_start = meta_stack->stack == first_element;
	}
	open_stack_ring(meta_stack->stack, meta_stack->last);
	return candidate;
}


