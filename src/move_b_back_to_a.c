#include "push_swap.h"


int	calc_moves_to_push_element_onto_a(t_list *a, t_list *b, t_list *push_candidate)
{
	return (calc_moves_to_get_a_in_push_position(a, push_candidate) + 1
		+ calc_moves_to_top(b, push_candidate));
	(void) a;
	(void) push_candidate;
}

/*
 	t_list	*first_element;
	t_list	*candidate;
	int		markup_count;
	int		global_max_markup_count;

	candidate = NULL;
	first_element = stack;
	global_max_markup_count = 0;
	while (stack && (! candidate || first_element != stack))
	{
		markup_count = count_markups(stack);
		if (! candidate || is_element_fitter_than_old_candidate(markup_count, global_max_markup_count, candidate, stack))
		{
			candidate = stack;
			global_max_markup_count = markup_count;
		}
		rotate(&stack, NULL);
	}
	return candidate;
 */