#include "libft/libft.h"
#include "push_swap.h"

// TODO: do i need to process the return value of the copy process?
void init_russian_algorithm(t_meta_stack *a, t_meta_stack **b, t_list **history,
							t_list **a_stack_cpy)
{
	(*a_stack_cpy) = ft_lstmap(a->stack, shallow_copy, do_not_free_content);
	(*b) = new_meta_stack();
	(*b)->is_stack_a = 0;
	(*b)->stack = NULL;
	(*history) = NULL;
}

t_list *russian_algorithm(t_meta_stack *a, enum markup_mode markup_mode)
{
	t_meta_stack	*b;
	t_list	*history;
	t_list			*a_stack_cpy;

	init_russian_algorithm(a, &b, &history, &a_stack_cpy);
	ft_putendl_fd("------------>a input", 1);
	ft_lstput_nbr_bonus(a->stack);
	fill_b(a, b, &history, markup_mode);
	ft_putendl_fd("a after fillb", 1);
	ft_lstput_nbr_bonus(a->stack);
	ft_putendl_fd("b after fillb", 1);
	ft_lstput_nbr_bonus(b->stack);
	sort_b_back_into_a(a, b, &history);
	ft_putendl_fd("a after sort back ino a ", 1);
	ft_lstput_nbr_bonus(a->stack);
	ft_putendl_fd("b after sort back ino a ", 1);
	ft_lstput_nbr_bonus(b->stack);
	ft_putendl_fd("sorted_back_a", 1);
	rotate_a_back_in_order(a, &history);
	ft_putendl_fd("------------>a sorted", 1);
	ft_lstput_nbr_bonus(a->stack);
	free(b);
	ft_lstclear(&a->stack, do_not_free_content);
	a->stack = a_stack_cpy;
	a->last = ft_lstlast(a->stack);
	ft_putendl_fd("done<------------\n", 1);
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
		ft_putendl_fd("not enough arguments", 2);
		return (0);
	}
	a = generate_stack(argc, argv + 1);

	if (! a)
	{
		ft_putendl_fd("Error",2);
		return (0);
	}
	history_index_mode = russian_algorithm(a, index_mode);
	history_value_mode = russian_algorithm(a, value_mode);
		ft_putendl_fd("------------value mode------------", 1);
	ft_lstput_str_bonus(history_value_mode);
		ft_putendl_fd("------------index mode------------", 1);
	ft_lstput_str_bonus(history_index_mode);
	ft_putstr_fd("operations needed for value mode: ", 1);
	ft_putnbr_fd(ft_lstsize(history_value_mode), 1);
	ft_putstr_fd("\n", 1);
	ft_putstr_fd("operations needed for index mode: ", 1);
	ft_putnbr_fd(ft_lstsize(history_index_mode), 1);
	ft_putstr_fd("\n", 1);
	ft_lstclear(&history_value_mode, do_not_free_content);
	ft_lstclear(&history_index_mode, do_not_free_content);
	ft_lstclear(&a->stack, free);
	free(a);
}
#endif