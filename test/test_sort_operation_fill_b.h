#include "test_utils.h"

Test(test_sort_operation_fill_b, does_not_do_anything_if_all_elements_should_stay, .disabled=0)
{
	t_list	*a = generate_stack_a(4);
	mark_stack_as_stay_on_a(a, 1);

	t_list	*b = NULL;
	t_list	*a_ref = a;
	while (a)
	{
		cr_expect_eq(CONTENT_OF_ELEMENT(a)->should_stay_on_stack_a, 1, "element %d", CONTENT_OF_ELEMENT(a)->i);
		a = a->next;
	}
	t_list	*b_ref = b;
	while (b)
	{
		cr_expect_eq(CONTENT_OF_ELEMENT(b)->should_stay_on_stack_a, 0, "element %d", CONTENT_OF_ELEMENT(b)->i);
		b = b->next;
	}
	ft_lstclear(&a_ref, free);
	ft_lstclear(&b_ref, free);
}

Test(test_sort_operation_fill_b, moves_all_to_b_if_no_element_marked_to_stay, .disabled=0)
{
	t_list	*a = generate_stack_a(4);
	mark_stack_as_stay_on_a(a, 0);
	t_list	*b = NULL;

	fill_b(&a, &b, NULL);

	t_list	*a_ref = a;
	while (a)
	{
		cr_expect_eq(CONTENT_OF_ELEMENT(a)->should_stay_on_stack_a, 1, "element %d", CONTENT_OF_ELEMENT(a)->i);
		a = a->next;
	}
	t_list	*b_ref = b;
	while (b)
	{
		cr_expect_eq(CONTENT_OF_ELEMENT(b)->should_stay_on_stack_a, 0, "element %d", CONTENT_OF_ELEMENT(b)->i);
		b = b->next;
	}
	ft_lstclear(&a_ref, free);
	ft_lstclear(&b_ref, free);
}


Test(test_sort_operation_fill_b, swaps_elements_if_makes_element_stay, .disabled=0)
{
	t_list	*a = generate_test_stack_0();
	t_list	*b = NULL;

	fill_b(&a, &b, NULL);

	t_list	*a_ref = a;
	while (a)
	{
		cr_expect_eq(CONTENT_OF_ELEMENT(a)->should_stay_on_stack_a, 1, "element %d", CONTENT_OF_ELEMENT(a)->i);
		a = a->next;
	}
	t_list	*b_ref = b;
	while (b)
	{
		cr_expect_eq(CONTENT_OF_ELEMENT(b)->should_stay_on_stack_a, 0, "element %d", CONTENT_OF_ELEMENT(b)->i);
		b = b->next;
	}
	ft_lstclear(&a_ref, free);
	ft_lstclear(&b_ref, free);
}

Test(test_sort_operation_fill_b, for_safety, .disabled=0)
{
	t_list	*a = generate_test_stack_2();
	t_list	*b = NULL;

	fill_b(&a, &b, NULL);

	t_list	*a_ref = a;
	while (a)
	{
		cr_expect_eq(CONTENT_OF_ELEMENT(a)->should_stay_on_stack_a, 1, "element %d", CONTENT_OF_ELEMENT(a)->i);
		a = a->next;
	}
	t_list	*b_ref = b;
	while (b)
	{
		cr_expect_eq(CONTENT_OF_ELEMENT(b)->should_stay_on_stack_a, 0, "element %d", CONTENT_OF_ELEMENT(b)->i);
		b = b->next;
	}
	ft_lstclear(&a_ref, free);
	ft_lstclear(&b_ref, free);
}

Test(test_sort_operation_fill_b, update_history_correctly, .disabled=1)
{
	t_list	*a = generate_test_stack_0();
	t_list	*b = NULL;
	t_list	*history = NULL;


	fill_b(&a, &b, &history);

	t_list	*a_ref = a;
	while (a)
	{
		cr_expect_eq(CONTENT_OF_ELEMENT(a)->should_stay_on_stack_a, 1, "element %d", CONTENT_OF_ELEMENT(a)->i);
		a = a->next;
	}
	t_list	*b_ref = b;
	while (b)
	{
		cr_expect_eq(CONTENT_OF_ELEMENT(b)->should_stay_on_stack_a, 0, "element %d", CONTENT_OF_ELEMENT(b)->i);
		b = b->next;
	}
	ft_lstput_str_bonus(history);
	ft_lstclear(&a_ref, free);
	ft_lstclear(&b_ref, free);
	ft_lstclear(&history, do_not_free_content);
}

Test(test_sort_operation_fill_b, do_noting_if_whole_stack_should_stay_on_a, .disabled=0)
{
	t_list	*a = generate_stack_a(2);
	mark_stack_as_stay_on_a(a, 1);
	t_list	*b = NULL;
	t_list	*history = NULL;


	fill_b(&a, &b, &history);

	cr_assert_null(history);
	ft_lstput_str_bonus(history);
	ft_lstclear(&history, do_not_free_content);
}
