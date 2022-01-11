/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <fschlute>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 09:02:12 by                   #+#    #+#             */
/*   Updated: 2021/12/14 13:18:46 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	size_t			ctr;

	ctr = 0;
	str = (unsigned char *) s;
	if (!n)
		return (NULL);
	while (*str != (unsigned char )c)
	{
		if (ctr++ == n - 1)
			return (NULL);
		str++;
	}
	return (str);
}
