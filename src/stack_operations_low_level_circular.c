/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_operations_low_level_circular.c              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <fschlute>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 09:00:50 by                   #+#    #+#             */
/*   Updated: 2021/11/23 09:00:59 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	close_stack_ring(t_list *stack, t_list *last_element)
{
	if (stack)
		stack->prev = last_element;
	if (last_element)
		last_element->next = stack;
}

void	open_stack_ring(t_list *stack, t_list *last_element)
{
	if (stack)
		stack->prev = NULL;
	if (last_element)
		last_element->next = NULL;
}
