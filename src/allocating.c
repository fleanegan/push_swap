/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocating.c 					                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <fschlute>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 09:00:50 by                   #+#    #+#             */
/*   Updated: 2021/11/23 09:00:59 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_content	*new_stack_content(int in)
{
	t_content	*result;

	result = malloc (sizeof(t_content));
	if (! result)
		return (NULL);
	result->i = in;
	result->index = -1;
	result->is_on_stack_a = 1;
	result->should_stay_on_stack_a = 0;
	return (result);
}

t_meta_stack	*new_meta_stack(void)
{
	t_meta_stack	*result;

	result = malloc(sizeof (t_meta_stack));
	if (! result)
		return (NULL);
	result->stack = NULL;
	result->size = 0;
	result->last = 0;
	result->is_stack_a = 1;
	return (result);
}
