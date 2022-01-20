/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_moves.c			                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <fschlute>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 09:00:50 by                   #+#    #+#             */
/*   Updated: 2021/11/23 09:00:59 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	calc_moves_to_push_element_onto_a(\
	t_meta_stack *a, t_meta_stack *b, t_list *push_candidate)
{
	return ((int)(\
	ft_abs(calc_moves_to_get_a_in_push_position(a, push_candidate)) + 1 \
	+ ft_abs(calc_moves_to_top(b, push_candidate))));
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

int	calc_moves_to_get_a_in_push_position(\
t_meta_stack *a, t_list *push_candidate)
{
	int		moves_for_minus_one;
	int		moves_for_plus_one;
	t_list	*minus_one;
	t_list	*plus_one;
	int		value_of_push_candidate;

	if (! a->stack)
		return (0);
	value_of_push_candidate = get_content_of_element(push_candidate)->i;
	minus_one = get_biggest_element_smaller_than_candidate(\
	a->stack, value_of_push_candidate);
	plus_one = get_smallest_element_bigger_than_candidate(\
	a->stack, value_of_push_candidate);
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
