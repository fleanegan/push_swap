#include "push_swap.h"
#include <stdio.h>

void	fill_b(t_list **a, t_list **b, t_list **history)
{
	t_list		*markup_reference;
	int			elements_to_move;

	elements_to_move = -1;
	markup_reference = calc_markup_reference(*a);
	elements_to_move = count_elements_to_be_moved_to_b(*a);
	while (elements_to_move && (*a) != NULL)
	{
		if (is_swapping_a_good_idea(*a, markup_reference))
		{
			swap_first_two_elements(a, history);
			reverse_rotate(a, history);
//		can i leave this one ?	markup_all_elements_according_to_reference(*a, markup_reference);
		}
		else if (! CONTENT_OF_ELEMENT(*a)->should_stay_on_stack_a)
			push_first_element_of_a_to_b(a, b, history);
		else
			reverse_rotate(a, history);
		elements_to_move--;
	}
}
