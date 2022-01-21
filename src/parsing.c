/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c 										     :+:     :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <fschlute>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 09:00:50 by                   #+#    #+#             */
/*   Updated: 2021/11/23 09:00:59 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "libft/libft_auxilliar.h"

int	is_str_parsable(char *in)
{
	int	contains_number;

	contains_number = 0;
	if (*in && (*in == '+' || *in == '-'))
		in++;
	while (*in)
	{
		contains_number = 1;
		if (! ft_isdigit(*in))
			return (0);
		in++;
	}
	return (contains_number);
}

int	does_fit_into_int(const char *in)
{
	int			sign;
	long int	res;

	sign = 1;
	res = 0;
	while (ft_isspace(*in))
		in++;
	if (*in == '-' || *in == '+')
	{
		if (*in == '-')
			sign = -1;
		in++;
	}
	while (ft_isdigit(*in))
	{
		res = 10 * res + (*in++ - '0');
		if ((res > INT_MAX && sign == 1)
			|| (res > (long) INT_MAX + 1 && sign == -1))
			return (0);
	}
	return (1);
}

int	does_contain_duplication(t_list	*stack, int compare_value)
{
	while (stack)
	{
		if (get_content_of_element(stack)->i == compare_value)
			return (1);
		stack = stack->next;
	}
	return (0);
}

t_content	*parse_one_string(char *in)
{
	t_content	*result;

	if (! is_str_parsable(in) || ! does_fit_into_int(in))
		return (NULL);
	result = new_stack_content(ft_atoi(in));
	return (result);
}

t_meta_stack	*generate_stack(int argc, const char **argv)
{
	t_meta_stack		*result;
	t_content			*new_content;
	t_list				*new_element;

	result = new_meta_stack();
	while (--argc)
	{
		new_content = parse_one_string(*(char **) argv);
		if (! result || ! new_content || does_contain_duplication(\
		result->stack, new_content->i))
		{
			ft_lstclear(&result->stack, free);
			free(new_content);
			free(result);
			return (NULL);
		}
		new_element = ft_lstnew(new_content);
		if (! new_element)
			return (NULL);
		ft_lstadd_back(&result->stack, new_element);
		result->size++;
		(char **) argv++;
	}
	index_stack(result->stack);
	result->last = ft_lstlast(result->stack);
	return (result);
}
