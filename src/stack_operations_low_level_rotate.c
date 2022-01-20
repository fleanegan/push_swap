/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_operations_low_level_rotate.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <fschlute>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 09:00:50 by                   #+#    #+#             */
/*   Updated: 2021/11/23 09:00:59 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "push_swap.h"

static void		update_history(t_list **history, int is_on_stack_a);
static t_list	*detach_last_element_from_list(t_list *stack);

void	rotate(t_meta_stack *meta_stack, t_list **history)
{
	t_list	*last_element;

	if (meta_stack->stack && meta_stack->stack->next)
	{
		last_element = detach_last_element_from_list(meta_stack->stack);
		meta_stack->last = last_element->prev;
		ft_lstadd_front(&meta_stack->stack, last_element);
		update_history(history, meta_stack->is_stack_a);
	}
}

t_list	*detach_last_element_from_list(t_list *stack)
{
	t_list	*result;

	while (stack->next && stack->next->next)
		stack = stack->next;
	result = stack->next;
	stack->next = NULL;
	return (result);
}

void	update_history(t_list **history, const int is_on_stack_a)
{
	if (!history)
		return ;
	if (is_on_stack_a)
		ft_lstadd_back(history, ft_lstnew("ra\n"));
	else
		ft_lstadd_back(history, ft_lstnew("rb\n"));
}
