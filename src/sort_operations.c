#include <stdio.h>
#include "push_swap.h"

// TODO: index is not a valid information once the stack has changed!
int	calc_direction_to_top(t_list *stack, t_list *element_to_move)
{
	int	stack_size;

	stack_size = ft_lstsize(stack);
	if (! stack_size || ! element_to_move)
		return (0);
	if (! (((t_content *)(element_to_move->content))->index))
		return (0);
	if (((t_content *)(element_to_move->content))->index <= stack_size / 2)
		return (-1);
	else
		return (1);
}

void move_to_top(t_list **stack, t_list *element_to_move, t_list **history)
{
	int direction;

	if (! stack)
		return ;
	direction = calc_direction_to_top(*stack, element_to_move);
	while (*stack && element_to_move && element_to_move != *stack)
	{
		if (direction == -1)
			reverse_rotate(stack, history);
		if (direction == 1)
			rotate(stack, history);
	}
}

int calc_moves_to_top(t_list *stack, t_list *element) {
	int	element_index;
	int	total_len;

	if (! stack)
		return (0);
	if (! element)
		return (-1);
	if (CONTENT_OF_ELEMENT(stack)->is_on_stack_a != CONTENT_OF_ELEMENT(element)->is_on_stack_a)
		return (-1);
	element_index = ft_lstget_index_of_element(stack, element);
	total_len = ft_lstsize(stack);
	// TODO replace with own abs
	return (calc_min_unsigned(abs(total_len - element_index), element_index));
}