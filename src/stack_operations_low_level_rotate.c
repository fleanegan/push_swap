/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_operations_low_level_rotate.c        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <fschlute>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 09:00:50 by                   #+#    #+#             */
/*   Updated: 2021/11/23 09:00:59 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void		update_history(t_list **history, int is_on_stack_a);
static t_list	*pop_first_element_from_list(t_list **stack);

void	rotate(t_meta_stack *meta_stack, t_list **history)
{
	t_list	*first_element;

	if (meta_stack->stack && meta_stack->stack->next)
	{
		first_element = pop_first_element_from_list(&meta_stack->stack);
		meta_stack->last = first_element;
		ft_lstadd_back(&meta_stack->stack, first_element);
		update_history(history, meta_stack->is_stack_a);
	}
}

t_list	*pop_first_element_from_list(t_list **stack)
{
	t_list	*tmp;

	tmp = *stack;
	*stack = (*stack)->next;
	tmp->next = NULL;
	(*stack)->prev = NULL;
	return (tmp);
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
