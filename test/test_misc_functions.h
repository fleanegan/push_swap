#include "test_utils.h"

Test(test_get_element_by_sort_index, normal_case_since_general_is_covered_in_libft)
{
	t_list	*a = generate_stack_a(5);

	t_list	*res_act = ft_lstget_element_by_function(a, sorting_index_equals_to, 1);

	cr_assert_eq(res_act, a->next, "res_act %d", CONTENT_OF_ELEMENT(res_act)->i);
	ft_lstclear(&a, free);
}

Test(test_get_biggest_element_smaller_than_candidate, empty_list_does_noting_and_return_NULL)
{
	t_list	*a = NULL;

	t_list	*res_act = get_biggest_element_smaller_than_candidate(a, a);

	cr_assert_null(res_act);
	ft_lstclear(&a, free);
}

Test(test_get_biggest_element_smaller_than_candidate, NULL_candidate_returns_NULL)
{
	t_list	*a = ft_lstnew(NULL);
	t_list	*push_candidate = NULL;

	t_list	*res_act = get_biggest_element_smaller_than_candidate(a, push_candidate);

	cr_assert_null(res_act);
	ft_lstclear(&a, free);
}

Test(test_get_biggest_element_smaller_than_candidate, return_element_smaller_than_candidate)
{
	t_list	*a = generate_stack_a(3);
	rotate(&a, NULL);
	t_list	*push_candidate = NULL;
	push_first_element_of_a_to_b(&a, &push_candidate, NULL);

	t_list	*res_act = get_biggest_element_smaller_than_candidate(a, push_candidate);

	cr_assert_eq(res_act, ft_lstlast(a));
	ft_lstclear(&a, free);
	ft_lstclear(&push_candidate, free);
}

Test(test_get_biggest_element_smaller_than_candidate, if_no_element_found_return_NULL)
{
	t_list	*a = generate_stack_a(2);
	t_list	*push_candidate = NULL;
	push_first_element_of_a_to_b(&a, &push_candidate, NULL);

	t_list	*res_act = get_biggest_element_smaller_than_candidate(a, push_candidate);

	cr_assert_null(res_act);
	ft_lstclear(&a, free);
	ft_lstclear(&push_candidate, free);
}

Test(test_get_biggest_element_smaller_than_candidate, one_element)
{
	t_list	*a = generate_stack_a(2);
	rotate(&a, NULL);
	t_list	*push_candidate = NULL;
	push_first_element_of_a_to_b(&a, &push_candidate, NULL);

	t_list	*res_act = get_biggest_element_smaller_than_candidate(a, push_candidate);

	cr_assert_eq(res_act, a);
	ft_lstclear(&a, free);
	ft_lstclear(&push_candidate, free);
}

Test(test_get_smallest_element_bigger_than_candidate, return_element_smaller_than_candidate)
{
	t_list	*a = generate_stack_a(3);
	t_list	*push_candidate = a;

	t_list	*res_act = get_smallest_element_bigger_than_candidate(a, push_candidate);

	cr_assert_eq(res_act, a);
	ft_lstclear(&a, free);
}