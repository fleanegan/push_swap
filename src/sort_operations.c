#include <stdio.h>
#include "push_swap.h"

int	calc_direction_to_top(t_list *stack, t_list *element_to_move)
{
	int	stack_size;

	if (! stack)
		return (-1);
	stack_size = ft_lstsize(stack);
	if (! stack_size || ! element_to_move)
		return (0);
	if (stack == element_to_move)
		return (0);
	if (ft_lstget_index_of_element(stack, element_to_move) <= stack_size / 2)
		return (-1);
	else
		return (1);
}

int	calc_direction_to_bottom(t_list *stack, t_list *element_to_move)
{
	int	stack_size;

	if (! stack)
		return (-1);
	stack_size = ft_lstsize(stack);
	if (! stack_size || ! element_to_move)
		return (0);
	if (ft_lstlast(stack) == element_to_move)
		return (0);
	if (ft_lstget_index_of_element(stack, element_to_move) >= stack_size / 2)
		return (-1);
	else
		return (1);
}

void	move_to_top(t_meta_stack *meta_stack, t_list *element_to_move, t_list **history)
{
	int	direction;

	if (! meta_stack)
		return ;
	direction = calc_direction_to_top(meta_stack->stack, element_to_move);
	while (meta_stack->stack && element_to_move && element_to_move != meta_stack->stack)
	{
		if (direction == -1)
			reverse_rotate(meta_stack, history);
		if (direction == 1)
			rotate(meta_stack, history);
	}
}

void	move_to_bottom(t_meta_stack *meta_stack, t_list *element_to_move, t_list **history)
{
	int	direction;

	if (! meta_stack)
		return ;
	direction = calc_direction_to_bottom(meta_stack->stack, element_to_move);
	while (meta_stack->stack && element_to_move && element_to_move != ft_lstlast(meta_stack->stack))
	{
		if (direction == -1)
			reverse_rotate(meta_stack, history);
		if (direction == 1)
			rotate(meta_stack, history);
	}
}

int	calc_moves_to_top(t_list *stack, t_list *element)
{
	unsigned int	element_index;
	unsigned int	stack_len;
	unsigned int	moves_upwards;
	unsigned int	moves_downwards;

	if (! stack)
		return (0);
	if (! element)
		return (-1);
	if (CONTENT_OF_ELEMENT(stack)->is_on_stack_a != CONTENT_OF_ELEMENT(element)->is_on_stack_a)
		return (-1);
	element_index = ft_lstget_index_of_element(stack, element);
	stack_len = ft_lstsize(stack);
	moves_downwards = ft_abs((int)(stack_len - element_index));
	moves_upwards = element_index;
	return ((int) calc_min_unsigned(moves_downwards, moves_upwards));
}

int	calc_moves_to_bottom(t_list *stack, t_list *element)
{
	unsigned int	element_index;
	unsigned int	stack_len;
	unsigned int	moves_upwards;
	unsigned int	moves_downwards;

	if (! stack)
		return (0);
	if (! element)
		return (-1);
	if (CONTENT_OF_ELEMENT(stack)->is_on_stack_a != CONTENT_OF_ELEMENT(element)->is_on_stack_a)
		return (-1);
	element_index = ft_lstget_index_of_element(stack, element);
	stack_len = ft_lstsize(stack);
	moves_downwards = stack_len - element_index - 1;
	moves_upwards = ft_abs((int)(element_index + 1));
	return ((int) calc_min_unsigned(moves_downwards, moves_upwards));
}

int	sorting_index_equals_to(void *content, int index)
{
	if (content)
		return (((t_content *)content)->index == index);
	return (0);
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
		moves_for_minus_one = calc_moves_to_bottom(a->stack, minus_one);
	else
	{
		move_to_bottom(a, plus_one, history);
		return ;
	}
	if (plus_one)
		moves_for_plus_one = calc_moves_to_top(a->stack, plus_one);
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

int	calc_moves_to_get_a_in_push_position(t_list *a, t_list *push_candidate)
{
	unsigned int		moves_for_minus_one;
	unsigned int		moves_for_plus_one;
	t_list				*minus_one;
	t_list				*plus_one;
	int					value_of_push_candidate;

	if (! a)
		return (1);
	value_of_push_candidate = CONTENT_OF_ELEMENT(push_candidate)->i;
	minus_one = get_biggest_element_smaller_than_candidate(a, value_of_push_candidate);
	plus_one = get_smallest_element_bigger_than_candidate(a, value_of_push_candidate);
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
