/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   russian_algorithm_move_b_back_to_a_auxiliary.c      :+:     :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <fschlute>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 09:00:50 by                   #+#    #+#             */
/*   Updated: 2021/11/23 09:00:59 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "push_swap.h"

t_list	*find_next_element_to_push(t_meta_stack *a, t_meta_stack *b)
{
	t_list	*result;
	t_list	*tmp;
	int		global_min;
	int		tmp_moves;

	tmp = b->stack;
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

void	russian_algorithm_move_b_back_to_a(\
		t_meta_stack *a, t_meta_stack *b, t_list **history)
{
	t_list	*element_to_push;

	while (a && b && b->stack)
	{
		element_to_push = find_next_element_to_push(a, b);
		move_to_top(b, element_to_push, history);
		bring_a_in_push_position(a, element_to_push, history);
		push_first_element_to_the_other_stack(b, a, history);
	}
}
