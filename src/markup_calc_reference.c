/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   markup_calc_reference.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <fschlute>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 09:00:50 by                   #+#    #+#             */
/*   Updated: 2021/11/23 09:00:59 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "push_swap.h"

int	is_element_fitter( const t_list *stack, \
const t_list *old_candidate)
{
	static int		global_max_markup_count = 0;
	int				markup_count;
	const t_list	*new_candidate;

	new_candidate = stack;
	markup_count = count_markups(stack);
	if (markup_count > global_max_markup_count \
		|| (markup_count == global_max_markup_count \
		&& get_content_of_element((t_list *) old_candidate)->index \
		> get_content_of_element((t_list *) new_candidate)->index))
	{
		global_max_markup_count = markup_count;
		return (1);
	}
	return (0);
}

t_list	*calc_markup_reference(\
t_meta_stack *meta_stack, enum e_markup_mode mode)
{
	t_list	*first_element;
	t_list	*candidate;
	int		is_done;

	is_done = 0;
	candidate = meta_stack->stack;
	first_element = meta_stack->stack;
	close_stack_ring(meta_stack->stack, meta_stack->last);
	while (! is_done)
	{
		markup_stack_by_reference(meta_stack, meta_stack->stack, mode);
		if (is_element_fitter(meta_stack->stack, candidate))
			candidate = meta_stack->stack;
		reverse_rotate(meta_stack, NULL);
		is_done = meta_stack->stack == first_element;
	}
	open_stack_ring(meta_stack->stack, meta_stack->last);
	return (candidate);
}
