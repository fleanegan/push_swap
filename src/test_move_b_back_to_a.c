#include <stdio.h>
#include "push_swap.h"

int	calc_moves_to_push_element_onto_a(t_list *a, t_list *b, t_list *push_candidate)
{
	return (calc_moves_to_get_a_in_push_position(a, push_candidate) + 1
		+ calc_moves_to_top(b, push_candidate));
}

t_list	*calc_element_to_push(t_list *a, t_list *b)
{
	t_list	*result;
	t_list	*tmp;
	int		global_min;
	int		tmp_moves;

	tmp = b;
	result = NULL;
	while (tmp)
	{
		tmp_moves = calc_moves_to_push_element_onto_a(a, b, tmp);
		if (! result || tmp_moves < global_min)
		{
			result = tmp;
			global_min = tmp_moves;
		}
		tmp = tmp->next;
	}
	return (result);
}

void	sort_b_back_into_a(t_meta_stack *a, t_meta_stack *b, t_list **history)
{
	t_list	*element_to_push;

	while (a && b && b->stack)
	{
		element_to_push = calc_element_to_push(a->stack, b->stack);
		move_to_top(b, element_to_push, history);
		bring_a_in_push_position(a, element_to_push, history);
		push_first_element_of_a_to_b(b, a, history);
	}
}
