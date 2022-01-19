#include "libft/libft.h"
#include "push_swap.h"

t_list *russian_algorithm(t_meta_stack *a, enum markup_mode markup_mode)
{
	t_meta_stack	*b;
	t_list	*history;

	b = new_meta_stack();
	b->is_stack_a = 0;
	b->stack = NULL;
	history = NULL;
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
	ft_putendl_fd("done<------------\n", 1);
	return (history);
}

#ifndef TESTING

int	main(int argc, const char **argv)
{
	t_meta_stack	*int_input;
	t_list			*history;

	if (argc < 2)
	{
		ft_putendl_fd("not enough arguments", 2);
		return (0);
	}
	int_input = generate_stack(argc, argv + 1);
	if (! int_input)
	{
		ft_putendl_fd("Error",2);
		return (0);
	}
	history = russian_algorithm(int_input, value_mode);
	ft_lstput_str_bonus(history);
	ft_putendl_fd("operations needed:", 1);
	ft_putnbr_fd(ft_lstsize(history), 1);
	ft_lstclear(&history, do_not_free_content);
	ft_lstclear(&int_input->stack, free);
	free(int_input);
}
#endif