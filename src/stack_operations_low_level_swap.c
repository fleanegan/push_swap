/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_operations_low_level_swap.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <fschlute>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 09:00:50 by                   #+#    #+#             */
/*   Updated: 2021/11/23 09:00:59 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	update_history(t_list **history, int is_on_stack_a);

void	swap_first_two_elements(t_meta_stack *meta_stack, t_list **history)
{
	t_list	*next_head;
	t_list	*current_head;

	if (meta_stack && meta_stack->stack && meta_stack->stack->next)
	{
		current_head = meta_stack->stack;
		next_head = current_head->next;
		if (next_head == meta_stack->last)
			meta_stack->last = meta_stack->stack;
		current_head->next = next_head->next;
		next_head->next = current_head;
		meta_stack->stack = next_head;
		next_head->prev = NULL;
		current_head->prev = next_head;
		if (current_head->next)
			current_head->next->prev = current_head;
		update_history(\
		history, meta_stack->is_stack_a);
	}
}

void	update_history(t_list **history, const int is_on_stack_a)
{
	if (!history)
		return ;
	if (is_on_stack_a)
		ft_lstadd_back(history, ft_lstnew("sa\n"));
	else
		ft_lstadd_back(history, ft_lstnew("sb\n"));
}
