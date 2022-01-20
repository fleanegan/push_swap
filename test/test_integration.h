#include "test_utils.h"

Test(test_integration, launching_russian_algorithm_does_not_change_a)
{
	t_meta_stack	*a = generate_test_stack_0();
	t_list			*cpy = ft_lstmap(a->stack, shallow_copy, do_not_free_content);

	russian_algorithm(a, value_mode);

	cr_assert(ft_lstcompare(a->stack, cpy, is_same_value));
}