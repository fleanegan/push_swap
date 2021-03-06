#include "test_utils.h"

Test(test_sort_operation_fill_b, NULL_test)
{
	t_meta_stack	*a = generate_stack_a(0);
	t_meta_stack	*b = generate_stack_b(0);
	russian_algorithm_move_unmarked_to_b(a, b, NULL, value_mode);
}

Test(test_sort_operation_fill_b, does_not_do_anything_if_all_elements_should_stay)
{
	t_meta_stack	*a = generate_stack_a(4);
	mark_stack_as_stay_on_a(a->stack, 1);
	t_meta_stack	*b = generate_stack_b(0);

	russian_algorithm_move_unmarked_to_b(a, b, NULL, value_mode);

	t_list	*a_ref = a->stack;
	while (a_ref)
	{
		cr_expect_eq(get_content_of_element(a_ref)->should_stay_on_stack_a, 1, "element %d",
					 get_content_of_element(a_ref)->i);
		a_ref = a_ref->next;
	}
	t_list	*b_ref = b->stack;
	while (b_ref)
	{
		cr_expect_eq(get_content_of_element(b_ref)->should_stay_on_stack_a, 0, "element %d",
					 get_content_of_element(b_ref)->i);
		b_ref = b_ref->next;
	}
	ft_lstclear(&a->stack, free);
	free(a);
	ft_lstclear(&b->stack, free);
	free(b);
}


Test(test_sort_operation_fill_b, moves_all_to_b_if_no_element_marked_to_stay)
{
	t_meta_stack	*a = generate_stack_a(4);
	mark_stack_as_stay_on_a(a->stack, 0);
	t_meta_stack	*b = generate_stack_b(0);

	russian_algorithm_move_unmarked_to_b(a, b, NULL, value_mode);

	t_list	*a_ref = a->stack;
	while (a_ref)
	{
		cr_expect_eq(get_content_of_element(a_ref)->should_stay_on_stack_a, 1, "element %d",
					 get_content_of_element(a_ref)->i);
		a_ref = a_ref->next;
	}
	t_list	*b_ref = b->stack;
	while (b_ref)
	{
		cr_expect_eq(get_content_of_element(b_ref)->should_stay_on_stack_a, 0, "element %d",
					 get_content_of_element(b_ref)->i);
		b_ref = b_ref->next;
	}
	ft_lstclear(&a->stack, free);
	free(a);
	ft_lstclear(&b->stack, free);
	free(b);
}

Test(test_sort_operation_fill_b, swaps_elements_if_makes_element_stay)
{
	t_meta_stack	*a = generate_test_stack_0();
	t_meta_stack	*b = generate_stack_b(0);

	russian_algorithm_move_unmarked_to_b(a, b, NULL, value_mode);

	t_list	*a_ref = a->stack;
	while (a_ref)
	{
		cr_expect_eq(get_content_of_element(a_ref)->should_stay_on_stack_a, 1, "element %d",
					 get_content_of_element(a_ref)->i);
		a_ref = a_ref->next;
	}
	t_list	*b_ref = b->stack;
	while (b_ref)
	{
		cr_expect_eq(get_content_of_element(b_ref)->should_stay_on_stack_a, 0, "element %d",
					 get_content_of_element(b_ref)->i);
		b_ref = b_ref->next;
	}
	ft_lstclear(&a->stack, free);
	free(a);
	ft_lstclear(&b->stack, free);
	free(b);
}

Test(test_sort_operation_fill_b, for_safety)
{
	t_meta_stack	*a = generate_test_stack_2();
	t_meta_stack	*b = generate_stack_b(0);

	russian_algorithm_move_unmarked_to_b(a, b, NULL, value_mode);

	t_list	*a_ref = a->stack;
	while (a_ref)
	{
		cr_expect_eq(get_content_of_element(a_ref)->should_stay_on_stack_a, 1, "element %d",
					 get_content_of_element(a_ref)->i);
		a_ref = a_ref->next;
	}
	t_list	*b_ref = b->stack;
	while (b_ref)
	{
		cr_expect_eq(get_content_of_element(b_ref)->should_stay_on_stack_a, 0, "element %d",
					 get_content_of_element(b_ref)->i);
		b_ref = b_ref->next;
	}
	ft_lstclear(&a->stack, free);
	free(a);
	ft_lstclear(&b->stack, free);
	free(b);
}

Test(test_sort_operation_fill_b, update_history_correctly)
{
	t_meta_stack	*a = generate_test_stack_1();
	t_meta_stack	*b = generate_stack_b(0);
	t_list			*history = NULL;

	russian_algorithm_move_unmarked_to_b(a, b, &history, value_mode);

	ft_lstclear(&a->stack, free);
	free(a);
	ft_lstclear(&b->stack, free);
	free(b);
}

Test(test_sort_operation_fill_b, do_noting_if_whole_stack_should_stay_on_a, .disabled=1)
{
	t_meta_stack	*a = generate_stack_a(2);
	mark_stack_as_stay_on_a(a->stack, 1);
	t_meta_stack	*b = generate_stack_b(0);
	t_list			*history = NULL;

	russian_algorithm_move_unmarked_to_b(a, b, &history, value_mode);

	ft_lstput_str_bonus(history);
	cr_assert_null(history);
	ft_lstclear(&a->stack, free);
	free(a);
	ft_lstclear(&b->stack, free);
	free(b);
}
