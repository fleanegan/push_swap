#include "test_utils.h"

Test(test_get_element_by_sort_index, normal_case_since_general_is_covered_in_libft)
{
	t_meta_stack	*a = generate_stack_a(5);

	t_list			*res_act = ft_lstget_element_by_function(a->stack, sorting_index_equals_to, 1);

	cr_assert_eq(res_act, a->stack->next, "res_act %d", CONTENT_OF_ELEMENT(res_act)->i);
	ft_lstclear(&a->stack, free);
	free(a);
}


Test(test_get_biggest_element_smaller_than_candidate, empty_list_does_noting_and_return_NULL)
{
	t_meta_stack	*a = generate_stack_a(0);
	t_list	*res_act = get_biggest_element_smaller_than_candidate(a->stack, 1);

	cr_assert_null(res_act);
	ft_lstclear(&a->stack, free);
	free(a);
}

Test(test_get_biggest_element_smaller_than_candidate, return_element_smaller_than_candidate)
{
	t_meta_stack	*a = generate_stack_a(3);
	rotate(a, NULL);
	t_meta_stack	*b = generate_stack_b(0);
	push_first_element_to_the_other_stack(a, b, NULL);

	t_list	*res_act = get_biggest_element_smaller_than_candidate(a->stack, CONTENT_OF_ELEMENT(b->stack)->i);

	cr_assert_eq(res_act, ft_lstlast(a->stack));
	ft_lstclear(&a->stack, free);
	free(a);
	ft_lstclear(&b->stack, free);
	free(b);
}

Test(test_get_biggest_element_smaller_than_candidate, if_no_element_found_return_NULL)
{
	t_meta_stack	*a = generate_stack_a(2);
	t_meta_stack	*b = generate_stack_b(0);
	push_first_element_to_the_other_stack(a, b, NULL);

	t_list	*res_act = get_biggest_element_smaller_than_candidate(a->stack, CONTENT_OF_ELEMENT(b->stack)->i);

	cr_assert_null(res_act);
	ft_lstclear(&a->stack, free);
	free(a);
	ft_lstclear(&b->stack, free);
	free(b);
}

Test(test_get_biggest_element_smaller_than_candidate, one_element)
{
	t_meta_stack	*a = generate_stack_a(3);
	reverse_rotate(a, NULL);
	t_meta_stack	*b = generate_stack_b(0);
	push_first_element_to_the_other_stack(a, b, NULL);

	t_list	*res_act = get_biggest_element_smaller_than_candidate(a->stack, CONTENT_OF_ELEMENT(b->stack)->i);

	cr_assert_eq(CONTENT_OF_ELEMENT(res_act)->i, 0);
	ft_lstclear(&a->stack, free);
	free(a);
	ft_lstclear(&b->stack, free);
	free(b);
}

Test(test_get_smallest_element_bigger_than_candidate, return_element_smaller_than_candidate)
{
	t_meta_stack	*a = generate_stack_a(3);
	t_list	*push_candidate = a->stack;

	t_list	*res_act = get_smallest_element_bigger_than_candidate(a->stack, CONTENT_OF_ELEMENT(push_candidate)->i);

	cr_assert_eq(res_act, a->stack);
	ft_lstclear(&a->stack, free);
	free(a);
}
