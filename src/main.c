/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c							                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <fschlute>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 09:00:50 by                   #+#    #+#             */
/*   Updated: 2021/11/23 09:00:59 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "push_swap.h"

// TODO: do i need to process the return value of the copy process?
void	init_russian_algorithm(t_meta_stack *a, \
t_meta_stack **b, t_list **history, t_list **a_stack_cpy)
{
	(*a_stack_cpy) = ft_lstmap(a->stack, shallow_copy, do_not_free_content);
	(*b) = new_meta_stack();
	(*b)->is_stack_a = 0;
	(*b)->stack = NULL;
	(*history) = NULL;
}

void	tear_down_russian_algorithm(t_meta_stack *a, \
t_meta_stack *b, t_list *a_stack_cpy)
{
	free(b);
	ft_lstclear(&a->stack, do_not_free_content);
	a->stack = a_stack_cpy;
	a->last = ft_lstlast(a->stack);
}

t_list	*russian_algorithm(t_meta_stack *a, enum e_markup_mode markup_mode)
{
	t_meta_stack	*b;
	t_list			*history;
	t_list			*a_stack_cpy;

	init_russian_algorithm(a, &b, &history, &a_stack_cpy);
	russian_algorithm_move_unmarked_to_b(a, b, &history, markup_mode);
	russian_algorithm_move_b_back_to_a(a, b, &history);
	rotate_a_back_in_order(a, &history);
	tear_down_russian_algorithm(a, b, a_stack_cpy);
	return (history);
}

#ifndef TESTING

int	main(int argc, const char **argv)
{
	t_meta_stack	*a;
	t_list			*history_value_mode;
	t_list			*history_index_mode;

	if (argc < 2)
	{
		ft_putendl_fd("Error", 2);
		return (0);
	}
	a = generate_stack(argc, argv + 1);
	if (! a)
	{
		ft_putendl_fd("Error", 2);
		return (0);
	}
	history_index_mode = russian_algorithm(a, index_mode);
	history_value_mode = russian_algorithm(a, value_mode);
	if (ft_lstsize(history_index_mode) < ft_lstsize(history_value_mode))
		ft_lstput_str_bonus(history_index_mode);
	else
		ft_lstput_str_bonus(history_value_mode);
	ft_lstclear(&history_value_mode, do_not_free_content);
	ft_lstclear(&history_index_mode, do_not_free_content);
	ft_lstclear(&a->stack, free);
	free(a);
}
#endif