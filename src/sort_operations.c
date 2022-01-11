#include "push_swap.h"

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

	while (stack && *stack && element_to_move && element_to_move != *stack)
	{
		direction = calc_direction_to_top(*stack, element_to_move);
		if (direction == -1)
			reverse_rotate(stack, history);
		if (direction == 1)
			rotate(stack, history);
	}
}
