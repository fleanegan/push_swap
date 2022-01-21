/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_operations_high_level.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <fschlute>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 09:00:50 by                   #+#    #+#             */
/*   Updated: 2021/11/23 09:00:59 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rotate_stack_n_steps(\
t_meta_stack *meta_stack, int steps, t_list **history)
{
	if (steps < 0)
	{
		while (steps < 0)
		{
			rotate(meta_stack, history);
			steps++;
		}
	}
	else
	{
		while (steps > 0)
		{
			reverse_rotate(meta_stack, history);
			steps--;
		}
	}
}

void	move_to_top(\
t_meta_stack *meta_stack, t_list *element_to_move, t_list **history)
{
	int	moves_to_top;

	moves_to_top = calc_moves_to_top(meta_stack, element_to_move);
	rotate_stack_n_steps(meta_stack, moves_to_top, history);
}

void	rotate_a_back_in_order(t_meta_stack *a, t_list **history)
{
	t_list	*smallest_element;

	smallest_element = get_smallest_element_bigger_than_candidate(\
	a->stack, INT_MIN);
	move_to_top(a, smallest_element, history);
}

void	bring_a_in_push_position(\
t_meta_stack *a, t_list *push_candidate, t_list **history)
{
	int	necessary_steps;

	necessary_steps = calc_moves_to_get_a_in_push_position(a, push_candidate);
	rotate_stack_n_steps(a, necessary_steps, history);
}
