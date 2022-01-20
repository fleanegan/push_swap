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

void fill_b(t_meta_stack *a, t_meta_stack *b, t_list **history,
			enum markup_mode markup_mode)
{
	t_list		*markup_reference;

	if (! a->stack)
		return ;
	all_prevs_are_properly_set(a);
	markup_reference = calc_markup_reference(a, markup_mode);
	markup_stack_by_reference(a, markup_reference, markup_mode);
	all_prevs_are_properly_set(a);
	while (a->stack && count_elements_to_be_moved_to_b(a))
	{
		markup_stack_by_reference(a, markup_reference,
								  markup_mode);
		if (is_swapping_a_good_idea(a, markup_reference, value_mode))
		{
			swap_first_two_elements(a, history);
//			reverse_rotate(a, history);
			rotate(a, history);
		}
		else if (! CONTENT_OF_ELEMENT(a->stack)->should_stay_on_stack_a)
			push_first_element_to_the_other_stack(a, b, history);
		else
		{
//			reverse_rotate(a, history);
			rotate(a, history);
		}
	}
}
