#include "libft/libft.h"
#include "push_swap.h"

t_list	*russian_algorithm(t_list *a)
{
	t_list	*b;
	t_list	*history;

	b = NULL;
	history = NULL;
	ft_putendl_fd("------------>a input", 1);
	ft_lstput_nbr_bonus(a);
	fill_b(&a, &b, &history);
	ft_putendl_fd("a after fillb", 1);
	ft_lstput_nbr_bonus(a);
	ft_putendl_fd("b after fillb", 1);
	ft_lstput_nbr_bonus(b);
	sort_b_back_into_a(&a, &b, &history);
	ft_putendl_fd("a after sort back ino a ", 1);
	ft_lstput_nbr_bonus(a);
	ft_putendl_fd("b after sort back ino a ", 1);
	ft_lstput_nbr_bonus(b);
	ft_putendl_fd("sorted_back_a", 1);
	rotate_a_back_in_order(&a, &history);
	ft_putendl_fd("------------>a sorted", 1);
	ft_lstput_nbr_bonus(a);
	ft_putendl_fd("done<------------\n", 1);
	return (history);
}

#ifndef TESTING

int	main(void)
{
	ft_putendl_fd("test", 1);
	return (0);
}
#endif