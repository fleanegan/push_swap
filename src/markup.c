/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   markup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <fschlute>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 09:00:50 by                   #+#    #+#             */
/*   Updated: 2021/11/23 09:00:59 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	init_global_max(const t_list *reference, const enum e_markup_mode *mode)
{
	if ((*mode) == value_mode)
		return (get_content_of_element((t_list *) reference)->i);
	return (get_content_of_element((t_list *) reference)->index);
}

void	markup_stack_by_reference(t_meta_stack *meta_stack, \
t_list *reference, enum e_markup_mode mode)
{
	int		is_done;
	int		global_max_value;
	t_list	*stack;

	is_done = 0;
	stack = reference;
	global_max_value = init_global_max(reference, &mode);
	close_stack_ring(meta_stack->stack, meta_stack->last);
	while (! is_done)
	{
		markup_one_element(stack, &global_max_value, mode);
		stack = stack->next;
		is_done = (stack == reference);
	}
	open_stack_ring(meta_stack->stack, meta_stack->last);
}

void	markup_element_in_value_mode(int *global_max, t_content *content)
{
	content->should_stay_on_stack_a = content->i >= *global_max;
	if (content->should_stay_on_stack_a)
		*global_max = content->i;
}

void	markup_element_in_index_mode(int *global_max, t_content *content)
{
	if (content->index == *global_max + 1 || content->index == *global_max)
		content->should_stay_on_stack_a = 1;
	else
		content->should_stay_on_stack_a = 0;
	if (content->should_stay_on_stack_a)
		(*global_max)++;
}

void	markup_one_element(t_list *element_to_be_marked_up, int *global_max, \
enum e_markup_mode mode)
{
	t_content	*content;

	content = get_content_of_element(element_to_be_marked_up);
	if (mode == value_mode)
		markup_element_in_value_mode(global_max, content);
	else
		markup_element_in_index_mode(global_max, content);
}
