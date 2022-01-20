/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_operations_low_level_push.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <fschlute>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 09:00:50 by                   #+#    #+#             */
/*   Updated: 2021/11/23 09:00:59 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "push_swap.h"

static void	update_history(t_list **history, int is_on_stack_a);
static void	cut_element_from_a_to_b(t_meta_stack *a, t_meta_stack *b);

void	push_first_element_to_the_other_stack(\
t_meta_stack *a, t_meta_stack *b, t_list **history)
{
	if (a && a->stack)
	{
		cut_element_from_a_to_b(a, b);
		a->size--;
		if (! b->size++)
			b->last = b->stack;
		update_history(\
		history, a->is_stack_a);
	}
}

void	cut_element_from_a_to_b(t_meta_stack *a, t_meta_stack *b)
{
	t_list		*tmp;

	tmp = a->stack->next;
	ft_lstadd_front(&b->stack, a->stack);
	a->stack = tmp;
	if (tmp)
		tmp->prev = NULL;
}

void	update_history(t_list **history, int is_on_stack_a)
{
	if (!history)
		return ;
	if (is_on_stack_a)
		ft_lstadd_back(history, ft_lstnew("pb\n"));
	else
		ft_lstadd_back(history, ft_lstnew("pa\n"));
}
