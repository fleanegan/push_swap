#include <stdio.h>
#include "push_swap.h"

void	rotate_stack_n_steps(t_meta_stack *meta_stack, int steps, t_list **history)
{
	if (steps < 0)
	{
		while (steps < 0)
		{
			reverse_rotate(meta_stack, history);
			steps++;
		}
	}
	else
	{
		while (steps > 0)
		{
			rotate(meta_stack, history);
			steps--;
		}
	}
}

void	move_to_top(t_meta_stack *meta_stack, t_list *element_to_move, t_list **history)
{
	int	moves_to_top;

	moves_to_top = calc_moves_to_top(meta_stack, element_to_move);
	rotate_stack_n_steps(meta_stack, moves_to_top, history);
}

int	calc_moves_to_top(t_meta_stack *meta_stack, t_list *element)
{
	int	element_index;
	int	moves_upwards;
	int	moves_downwards;

	if (! meta_stack->stack)
		return (0);
	element_index = ft_lstget_index_of_element(meta_stack->stack, element);
	moves_downwards = (int) meta_stack->size - element_index;
	moves_upwards = element_index;
	if (ft_abs(moves_downwards) < ft_abs(moves_upwards))
		return (moves_downwards);
	else
		return (-1 * moves_upwards);
}
//	printf("size %d, element index %d, upwards %d, downwards %d\n", (int)meta_stack->size, element_index, moves_upwards, moves_downwards);

int	calc_moves_to_bottom(t_meta_stack *meta_stack, t_list *element)
{
	int	element_index;
	int	moves_upwards;
	int	moves_downwards;

	if (! meta_stack->stack)
		return (0);
	element_index = ft_lstget_index_of_element(meta_stack->stack, element);
	moves_downwards = (int) meta_stack->size - element_index - 1;
	moves_upwards = element_index + 1;
	if (ft_abs(moves_downwards) < ft_abs(moves_upwards))
		return (moves_downwards);
	else
		return (-1 * moves_upwards);
}

void	rotate_a_back_in_order(t_meta_stack *a, t_list **history)
{
	t_list	*smallest_element;

	smallest_element = get_smallest_element_bigger_than_candidate(a->stack, INT_MIN);
	move_to_top(a, smallest_element, history);
}

void	bring_a_in_push_position(t_meta_stack *a, t_list *push_candidate, t_list **history)
{
	int	necessary_steps;

	necessary_steps = calc_moves_to_get_a_in_push_position(a, push_candidate);
	rotate_stack_n_steps(a, necessary_steps, history);
}

int	calc_moves_to_get_a_in_push_position(t_meta_stack *a, t_list *push_candidate)
{
	int		moves_for_minus_one;
	int		moves_for_plus_one;
	t_list	*minus_one;
	t_list	*plus_one;
	int		value_of_push_candidate;

	if (! a->stack)
		return (0);
	value_of_push_candidate = CONTENT_OF_ELEMENT(push_candidate)->i;
	minus_one = get_biggest_element_smaller_than_candidate(a->stack, value_of_push_candidate);
	plus_one = get_smallest_element_bigger_than_candidate(a->stack, value_of_push_candidate);
	if (! minus_one)
		return (calc_moves_to_top(a, plus_one));
	moves_for_minus_one = calc_moves_to_bottom(a, minus_one);
	if (! plus_one)
		return (calc_moves_to_bottom(a, minus_one));
	moves_for_plus_one = calc_moves_to_top(a, plus_one);
	if (ft_abs(moves_for_minus_one) < ft_abs(moves_for_plus_one))
		return (moves_for_minus_one);
	else
		return (moves_for_plus_one);
}
