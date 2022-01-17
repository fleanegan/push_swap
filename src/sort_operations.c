#include <stdio.h>
#include "push_swap.h"

void rotate_stack_n_steps(t_meta_stack *meta_stack, int steps, t_list **history)
{
	if (steps < 0)
		while (steps < 0)
		{
			reverse_rotate(meta_stack, history);
			steps++;
		}
	else
		while (steps > 0)
		{
			rotate(meta_stack, history);
			steps--;
		}
}

void	move_to_top(t_meta_stack *meta_stack, t_list *element_to_move, t_list **history)
{
	int moves_to_top;

	moves_to_top = calc_moves_to_top(meta_stack, element_to_move);
	rotate_stack_n_steps(meta_stack, moves_to_top, history);
}
//printf("moves to top %d\n", moves_to_top);

void	move_to_bottom(t_meta_stack *meta_stack, t_list *element_to_move, t_list **history)
{
	int moves_to_bottom;

	moves_to_bottom = calc_moves_to_bottom(meta_stack, element_to_move);
	rotate_stack_n_steps(meta_stack, moves_to_bottom, history);
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

void bring_a_in_push_position(t_meta_stack *a, t_list *push_candidate, t_list **history)
{
	unsigned int		moves_for_minus_one;
	unsigned int		moves_for_plus_one;
	t_list				*minus_one;
	t_list				*plus_one;
	int					value_of_push_candidate;

	value_of_push_candidate = CONTENT_OF_ELEMENT(push_candidate)->i;
	minus_one = get_biggest_element_smaller_than_candidate(a->stack, value_of_push_candidate);
	plus_one = get_smallest_element_bigger_than_candidate(a->stack, value_of_push_candidate);
	if (minus_one)
		moves_for_minus_one = calc_moves_to_bottom(a, minus_one);
	else
	{
		move_to_bottom(a, plus_one, history);
		return ;
	}
	if (plus_one)
		moves_for_plus_one = calc_moves_to_top(a, plus_one);
	else
	{
		move_to_top(a, minus_one, history);
		return ;
	}
	if (moves_for_plus_one < moves_for_minus_one)
		move_to_top(a, plus_one, history);
	else
		move_to_bottom(a, minus_one, history);
}

int	calc_moves_to_get_a_in_push_position(t_meta_stack *a, t_list *push_candidate)
{
	unsigned int		moves_for_minus_one;
	unsigned int		moves_for_plus_one;
	t_list				*minus_one;
	t_list				*plus_one;
	int					value_of_push_candidate;

	if (! a->stack)
		return (0);
	value_of_push_candidate = CONTENT_OF_ELEMENT(push_candidate)->i;
	minus_one = get_biggest_element_smaller_than_candidate(a->stack, value_of_push_candidate);
	plus_one = get_smallest_element_bigger_than_candidate(a->stack, value_of_push_candidate);
	if (minus_one)
		moves_for_minus_one = calc_moves_to_bottom(a, minus_one);
	else
		moves_for_minus_one = INT_MAX;
	if (plus_one)
		moves_for_plus_one = calc_moves_to_top(a, plus_one);
	else
		moves_for_plus_one = INT_MAX;
	return (calc_min_unsigned(moves_for_plus_one, moves_for_minus_one));
}
