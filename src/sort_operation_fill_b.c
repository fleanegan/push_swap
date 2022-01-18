#include "push_swap.h"
#include <stdio.h>

void	fill_b(t_meta_stack *a, t_meta_stack *b, t_list **history)
{
	t_list		*markup_reference;

	if (! a->stack)
		return ;
	printf("start filling b\n");
	markup_reference = calc_markup_reference(a);
	printf("markup reference is %d\n", CONTENT_OF_ELEMENT(markup_reference)->i);
	markup_all_elements_according_to_reference(a, markup_reference);
	puts("marked_up all elements");
	while (a->stack && count_elements_to_be_moved_to_b(a->stack))
	{
		printf("element on top is %d\n", CONTENT_OF_ELEMENT(a->stack)->i);
		markup_all_elements_according_to_reference(a, markup_reference);
		if (is_swapping_a_good_idea(a, markup_reference))
		{
			puts("te");
			swap_first_two_elements(a, history);
			rotate(a, history);
//			reverse_rotate(a, history);
		}
		else if (! CONTENT_OF_ELEMENT(a->stack)->should_stay_on_stack_a)
		{
			puts("tah????");
			push_first_element_to_the_other_stack(a, b, history);
		}
		else
		{
			puts("rotate");
			rotate(a, history);
		}
//			reverse_rotate(a, history);
	}
}
