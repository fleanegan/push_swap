/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   russian_algorithm_move_unmarked_to_b.c				:+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <fschlute>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 09:00:50 by                   #+#    #+#             */
/*   Updated: 2021/11/23 09:00:59 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	russian_algorithm_move_unmarked_to_b(t_meta_stack *a, \
		t_meta_stack *b, t_list **history, enum e_markup_mode mode)
{
	t_list		*markup_reference;
	int			is_done;

	is_done = 0;
	if (! a->stack)
		return ;
	markup_reference = calc_markup_reference(a, mode);
	while (! is_done)
	{
		markup_stack_by_reference(a, markup_reference, mode);
		if (is_swapping_a_good_idea(a, markup_reference, mode))
			swap_first_two_elements(a, history);
		else if (!get_content_of_element(a->stack)->should_stay_on_stack_a)
		{
			push_first_element_to_the_other_stack(a, b, history);
			continue ;
		}
		markup_stack_by_reference(a, markup_reference, mode);
		is_done = count_markups(a->stack) == (int) a->size;
		if (!is_done)
			rotate(a, history);
	}
}
