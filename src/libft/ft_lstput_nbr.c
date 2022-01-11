/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstput_nbr_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <fschlute>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 16:33:09 by                   #+#    #+#             */
/*   Updated: 2021/11/23 16:34:19 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstput_nbr_bonus(t_list *lst)
{
	while (lst)
	{
		ft_putnbr_fd(*(int *)lst->content, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		lst = lst->next;
	}
}

void	ft_lstput_char_bonus(t_list *lst)
{
	while (lst)
	{
		ft_putnbr_fd(*(char *)lst->content, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		lst = lst->next;
	}
}
