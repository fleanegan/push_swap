#ifndef TEST_UTILS_H
# define TEST_UTILS_H

# include <time.h>
# include "libft_auxilliar.h"
# include "push_swap.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <libft.h>
# include <criterion/criterion.h>
# include <criterion/theories.h>
# include <criterion/redirect.h>
# include <ctype.h>
# include <string.h>
# include <limits.h>

int	*malloc_int(int in)
{
	int	*result;

	result = malloc (sizeof(int));
	*result = in;
	return (result);
}

t_list	*generate_stack_a(int number_of_elements)
{
	t_list	*result;
	t_list	*tmp;

	result = NULL;
	for (int i = 0; i < number_of_elements; i++)
	{
		tmp = ft_lstnew(new_stack_content(i));
		ft_lstadd_back(&result, tmp);
	}
	index_stack(result);
	return (result);
}

t_list *generate_stack_b(int number_of_elements)
{
	t_list	*stack;
	t_list	*cpy;

	stack = generate_stack_a(number_of_elements);
	cpy = stack;
	while (cpy)
	{
		CONTENT_OF_ELEMENT(cpy)->is_on_stack_a = 0;
		cpy = cpy->next;
	}
	return (stack);
}

t_list	*generate_test_stack_0()
{
	t_list	*stack = ft_lstnew(new_stack_content(30));
	ft_lstadd_back(&stack, ft_lstnew(new_stack_content(2)));
	ft_lstadd_back(&stack, ft_lstnew(new_stack_content(-2)));
	ft_lstadd_back(&stack, ft_lstnew(new_stack_content(4)));
	ft_lstadd_back(&stack, ft_lstnew(new_stack_content(3)));
	ft_lstadd_back(&stack, ft_lstnew(new_stack_content(0)));
	ft_lstadd_back(&stack, ft_lstnew(new_stack_content(31)));
	index_stack(stack);
	return (stack);
}

t_list	*generate_test_stack_1()
{
	t_list	*stack = ft_lstnew(new_stack_content(2));
	ft_lstadd_back(&stack, ft_lstnew(new_stack_content(-2)));
	ft_lstadd_back(&stack, ft_lstnew(new_stack_content(4)));
	ft_lstadd_back(&stack, ft_lstnew(new_stack_content(3)));
	ft_lstadd_back(&stack, ft_lstnew(new_stack_content(0)));
	ft_lstadd_back(&stack, ft_lstnew(new_stack_content(31)));
	ft_lstadd_back(&stack, ft_lstnew(new_stack_content(-2)));
	index_stack(stack);
	return (stack);
}

t_list	*generate_test_stack_2()
{
	t_list	*stack = ft_lstnew(new_stack_content(2));
	ft_lstadd_back(&stack, ft_lstnew(new_stack_content(3)));
	ft_lstadd_back(&stack, ft_lstnew(new_stack_content(4)));
	ft_lstadd_back(&stack, ft_lstnew(new_stack_content(31)));
	ft_lstadd_back(&stack, ft_lstnew(new_stack_content(-2)));
	index_stack(stack);
	return (stack);
}

void	mark_stack_as_move_to_b(t_list *stack, int value)
{
	while (stack)
	{
		CONTENT_OF_ELEMENT(stack)->should_stay_on_stack_a = value;
		stack = stack->next;
	}
}

int	is_same_value(void *a, void *b)
{
	return (((t_content *)(a))->i == ((t_content *)(b))->i);
}

#endif	 // TEST_UTILS_H
