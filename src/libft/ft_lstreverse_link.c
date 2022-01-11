/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstreverse_link_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <fschlute>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 09:02:08 by                   #+#    #+#             */
/*   Updated: 2021/11/23 09:05:10 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstreverse(t_list *lst)
{
	t_list	*previous;
	t_list	*next;

	previous = NULL;
	while (lst)
	{
		next = lst->next;
		lst->next = previous;
		previous = lst;
		lst = next;
	}
	return (previous);
}
