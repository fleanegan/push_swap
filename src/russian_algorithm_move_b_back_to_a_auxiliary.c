/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c 				                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <fschlute>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 09:00:50 by                   #+#    #+#             */
/*   Updated: 2021/11/23 09:00:59 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	maximizing_result(t_list *a, int candidate_value, t_list **tmp)
{
	if (get_content_of_element(a)->i <= candidate_value
		&& (! *tmp
			|| get_content_of_element(a)->i > get_content_of_element(*tmp)->i))
		*tmp = a;
}

static void	minimizing_result(t_list *a, int candidate_value, t_list **tmp)
{
	if (get_content_of_element(a)->i >= candidate_value
		&& (! *tmp
			|| get_content_of_element(a)->i < get_content_of_element(*tmp)->i))
		*tmp = a;
}

static t_list	*get_element_which_is(t_list *a, int value_of_candidate, \
void (*element_comparison)(t_list *a, int value_of_candidate, t_list **result))
{
	t_list		*result;

	result = NULL;
	while (a)
	{
		element_comparison(a, value_of_candidate, &result);
		a = a->next;
	}
	return (result);
}

t_list	*get_biggest_element_smaller_than_candidate(\
		t_list *a, int value_of_candidate)
{
	if (! a)
		return (NULL);
	return (get_element_which_is(a, value_of_candidate, maximizing_result));
}

t_list	*get_smallest_element_bigger_than_candidate(\
		t_list *a, int value_of_candidate)
{
	if (! a)
		return (NULL);
	return (get_element_which_is(a, value_of_candidate, minimizing_result));
}
