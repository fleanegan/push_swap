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

int all_prevs_are_properly_set(t_meta_stack *meta_stack)
{
	t_list 			*stack = meta_stack->stack->next;

	while (stack)
	{
		if(! stack->prev)
			return (0);
		stack = stack->next;
	}
	return (1);
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
	meta_stack->last = ft_lstlast(meta_stack->stack);
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
		get_content_of_element(cpy)->is_on_stack_a = 0;
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
	result->size = ft_lstsize(result->stack);
	result->last = ft_lstlast(result->stack);
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
	result->size = ft_lstsize(result->stack);
	result->last = ft_lstlast(result->stack);
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
	result->size = ft_lstsize(result->stack);
	result->last = ft_lstlast(result->stack);
	return (result);
}

t_meta_stack	*generate_loop_bug_stack()
{
	char	*in = "3 1 2 4 5";
	char	**argv = ft_split(in, ' ');
	t_meta_stack  *result = generate_stack(5, (const char **) argv);
	free_2d_char_array(argv);
	return (result);
}

t_meta_stack	*generate_stack_from_str(int argc, char *in)
{
	char	**argv = ft_split(in, ' ');
	t_meta_stack  *result = generate_stack(argc, (const char **) argv);
	free_2d_char_array(argv);
	return (result);
}

t_meta_stack	*generate_minimal_crash_stack()
{
	char	*in = {"0 3 2 -1"};
	char	**argv = ft_split(in, ' ');
	t_meta_stack  *result = generate_stack(5, (const char **) argv);
	free_2d_char_array(argv);
	return (result);
}

t_meta_stack	*generate_huge_stack()
{
	char	*in = {"84 76 148 124 31 137 18 90 52 73 11 114 117 105 92 27 103 133 101 54 21 93 66 17 115 12 140 72 145 79 69 30 38 123 10 57 149 113 37 94 8 48 146 33 128 68 126 19 139 7 49 55 136 107 142 91 44 112 45 61 106 36 22 98 95 51 64 23 46 118 134 116 74 15 25 104 28 85 60 43 16 71 144 58 41 70 67 135 99 108 24 131 47 83 75 6 120 122 42 111 65 13 4 127 110 78 129 82 26 9 53 87 125 14 35 62 1 86 132 0 89 80 119 50 3 147 63 32 56 138 141 88 97 102 81 29 100 39 96 40 34 20 121 2 130 109 143 59 5 77"};
	char	**argv = ft_split(in, ' ');
	t_meta_stack  *result = generate_stack(151, (const char **) argv);
	free_2d_char_array(argv);
	return (result);
}

void	mark_stack_as_stay_on_a(t_list *stack, int value)
{
	while (stack)
	{
		get_content_of_element(stack)->should_stay_on_stack_a = value;
		stack = stack->next;
	}
}

int	is_same_value(void *a, void *b)
{
	return (((t_content *)(a))->i == ((t_content *)(b))->i);
}

#endif	 // TEST_UTILS_H
