#include "push_swap.h"
#include <stdio.h>

void	fill_b(t_meta_stack *a, t_meta_stack *b, t_list **history)
{
	t_list		*markup_reference;

	if (! a->stack)
		return ;
	markup_reference = calc_markup_reference(a);
	markup_all_elements_according_to_reference(a, markup_reference);
	while (a->stack && count_elements_to_be_moved_to_b(a->stack))
	{
		markup_all_elements_according_to_reference(a, markup_reference);
		if (is_swapping_a_good_idea(a, markup_reference))
		{
			swap_first_two_elements(a, history);
			rotate(a, history);
//			reverse_rotate(a, history);
		}
		else if (! CONTENT_OF_ELEMENT(a->stack)->should_stay_on_stack_a)
			push_first_element_of_a_to_b(a, b, history);
		else
			rotate(a, history);
//			reverse_rotate(a, history);
	}
}
