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

t_meta_stack	*generate_stack_a(int number_of_elements)
{
	t_meta_stack	*meta_stack;
	t_list			*tmp;

	meta_stack = new_meta_stack();
	for (int i = 0; i < number_of_elements; i++)
	{
		tmp = ft_lstnew(new_stack_content(i));
		ft_lstadd_back(&meta_stack->stack, tmp);
	}
	index_stack(meta_stack->stack);
	meta_stack->size = ft_lstsize(meta_stack->stack);
	return (meta_stack);
}

t_meta_stack	*generate_stack_b(int number_of_elements)
{
	t_meta_stack	*meta_stack;
	t_list			*cpy;

	meta_stack = generate_stack_a(number_of_elements);
	meta_stack->is_stack_a = 0;
	cpy = meta_stack->stack;
	while (cpy)
	{
		CONTENT_OF_ELEMENT(cpy)->is_on_stack_a = 0;
		cpy = cpy->next;
	}
	return (meta_stack);
}

t_meta_stack	*generate_test_stack_0()
{
	t_meta_stack	*result = new_meta_stack();
	result->stack = ft_lstnew(new_stack_content(30));
	ft_lstadd_back(&result->stack, ft_lstnew(new_stack_content(2)));
	ft_lstadd_back(&result->stack, ft_lstnew(new_stack_content(-2)));
	ft_lstadd_back(&result->stack, ft_lstnew(new_stack_content(4)));
	ft_lstadd_back(&result->stack, ft_lstnew(new_stack_content(3)));
	ft_lstadd_back(&result->stack, ft_lstnew(new_stack_content(0)));
	ft_lstadd_back(&result->stack, ft_lstnew(new_stack_content(31)));
	index_stack(result->stack);
	return (result);
}

t_meta_stack	*generate_test_stack_1()
{
	t_meta_stack	*result = new_meta_stack();
	result->stack = ft_lstnew(new_stack_content(2));
	ft_lstadd_back(&result->stack, ft_lstnew(new_stack_content(-2)));
	ft_lstadd_back(&result->stack, ft_lstnew(new_stack_content(4)));
	ft_lstadd_back(&result->stack, ft_lstnew(new_stack_content(3)));
	ft_lstadd_back(&result->stack, ft_lstnew(new_stack_content(0)));
	ft_lstadd_back(&result->stack, ft_lstnew(new_stack_content(31)));
	ft_lstadd_back(&result->stack, ft_lstnew(new_stack_content(-2)));
	index_stack(result->stack);
	return (result);
}

t_meta_stack	*generate_test_stack_2()
{
	t_meta_stack	*result = new_meta_stack();
	result->stack = ft_lstnew(new_stack_content(2));
	ft_lstadd_back(&result->stack, ft_lstnew(new_stack_content(3)));
	ft_lstadd_back(&result->stack, ft_lstnew(new_stack_content(4)));
	ft_lstadd_back(&result->stack, ft_lstnew(new_stack_content(31)));
	ft_lstadd_back(&result->stack, ft_lstnew(new_stack_content(-2)));
	index_stack(result->stack);
	return (result);
}

void	mark_stack_as_stay_on_a(t_list *stack, int value)
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
