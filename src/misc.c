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

int	sorting_index_equals_to(void *content, int index)
{
	if (content)
		return (((t_content *)content)->index == index);
	return (0);
}

t_content	*get_content_of_element(t_list *in)
{
	return (((t_content *)((in)->content)));
}
