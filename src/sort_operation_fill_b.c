#include "push_swap.h"

int all_prevs_are_properly_set(t_meta_stack *meta_stack)
{
	t_list 			*stack = meta_stack->stack->next;

	while (stack)
	{
		if(! stack->prev)
			return (0);
		stack = stack->next;
	}
	return (1);
}

void	fill_b(t_meta_stack *a, t_meta_stack *b, t_list **history)
{
	t_list		*markup_reference;

	if (! a->stack)
		return ;
	all_prevs_are_properly_set(a);
	markup_reference = calc_markup_reference(a);
	markup_all_elements_according_to_reference(a, markup_reference);
	all_prevs_are_properly_set(a);
	while (a->stack && count_elements_to_be_moved_to_b(a->stack))
	{
		markup_all_elements_according_to_reference(a, markup_reference);
		if (is_swapping_a_good_idea(a, markup_reference))
		{
			swap_first_two_elements(a, history);
			reverse_rotate(a, history);
		}
		else if (! CONTENT_OF_ELEMENT(a->stack)->should_stay_on_stack_a)
			push_first_element_to_the_other_stack(a, b, history);
		else
			reverse_rotate(a, history);
	}
}
