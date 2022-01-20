#include "test_utils.h"

Test(test_markup_single_element, with_higher_number_stays_on_list)
{
	t_meta_stack	*meta_stack = generate_stack_a(2);
	int				global_max = INT_MIN;
	t_list	*element_to_be_marked_up = meta_stack->stack->next;

	markup_one_element(element_to_be_marked_up, &global_max,
					   value_mode);

	cr_assert_eq(CONTENT_OF_ELEMENT(element_to_be_marked_up)->should_stay_on_stack_a, 1);
	ft_lstclear(&meta_stack->stack, free);
	free(meta_stack);
}

Test(test_markup_single_element, updates_global_max)
{
	t_meta_stack	*meta_stack = generate_stack_a(2);
	int				global_max = INT_MIN;
	t_list	*element_to_be_marked_up = meta_stack->stack->next;

	markup_one_element(element_to_be_marked_up, &global_max,
					   value_mode);

	cr_assert_eq(global_max, 1);
	ft_lstclear(&meta_stack->stack, free);
	free(meta_stack);
}

Test(test_markup_single_element, with_higher_number_does_not_stay_on_list_if_below_global_max)
{
	t_meta_stack	*meta_stack = generate_stack_a(2);
	int				global_max = INT_MAX;
	t_list	*element_to_be_marked_up = meta_stack->stack->next;

	markup_one_element(element_to_be_marked_up, &global_max,
					   value_mode);

	cr_assert_eq(CONTENT_OF_ELEMENT(element_to_be_marked_up)->should_stay_on_stack_a, 0);
	ft_lstclear(&meta_stack->stack, free);
	free(meta_stack);
}

Test(test_markup_single_element, in_index_mode_a_bigger_element_is_refused_if_index_jump)
{
	t_meta_stack	*meta_stack = generate_test_stack_0();
	t_list			*element_to_be_marked_up = ft_lstget_element_by_index(meta_stack->stack, 3);
	int				global_max = 0;

	markup_one_element(element_to_be_marked_up, &global_max, index_mode);

	cr_assert_eq(CONTENT_OF_ELEMENT(element_to_be_marked_up)->should_stay_on_stack_a, 0);
	ft_lstclear(&meta_stack->stack, free);
	free(meta_stack);
}

Test(test_markup_single_element, in_index_mode_after_successful_markup_global_max_increments)
{
	t_meta_stack	*meta_stack = generate_test_stack_0();
	t_list			*element_to_be_marked_up = ft_lstget_element_by_index(meta_stack->stack, 3);
	int				global_max = CONTENT_OF_ELEMENT(element_to_be_marked_up)->index - 1;

	markup_one_element(element_to_be_marked_up, &global_max, index_mode);

	cr_assert_eq(global_max, CONTENT_OF_ELEMENT(element_to_be_marked_up)->index);
	ft_lstclear(&meta_stack->stack, free);
	free(meta_stack);
}

Test(test_markup_count_for_element, count_equals_to_elements_greater_or_equal_to_head_of_stack)
{
	t_meta_stack	*meta_stack = generate_test_stack_0();
	markup_stack_by_reference(meta_stack, meta_stack->stack,
							  value_mode);

	int number_of_elements_which_stay_on_a = count_markups(meta_stack->stack);

	cr_assert_eq(number_of_elements_which_stay_on_a, 2);
	ft_lstclear(&meta_stack->stack, free);
	free(meta_stack);
}

Test(test_markup_count_for_element, no_one_stays_in_a)
{
	t_meta_stack	*a = generate_stack_a(3);
	mark_stack_as_stay_on_a(a->stack, 0);

	int number_of_elements_which_need_to_be_pushed = count_elements_to_be_moved_to_b(a);

	cr_assert_eq(number_of_elements_which_need_to_be_pushed, 3);
	ft_lstclear(&a->stack, free);
	free(a);
}

Test(test_markup_all_elements_of_stack, markup_elements)
{
	t_meta_stack	*a = generate_test_stack_0();
	t_list	*markup_reference = calc_markup_reference(a, value_mode);
	markup_stack_by_reference(a, markup_reference, value_mode);

	int	markup_count = count_markups(a->stack);

	cr_assert_eq(markup_count, 3, "markupcount %d", markup_count);
	ft_lstclear(&a->stack, free);
	free(a);
}

Test(test_markup_all_elements_of_stack, markup_list_with_one_element)
{
	t_meta_stack	*a = generate_stack_a(1);
	markup_stack_by_reference(a, a->stack, value_mode);

	int	markup_count = count_markups(a->stack);

	cr_assert_eq(markup_count, 1, "markupcount %d", markup_count);
	ft_lstclear(&a->stack, free);
	free(a);
}

Test(test_markup_all_elements_of_stack, markup_complex_stack)
{
	t_meta_stack	*meta_stack = generate_test_stack_2();
	t_list	*markup_reference = calc_markup_reference(meta_stack, value_mode);;

	markup_stack_by_reference(meta_stack, markup_reference,
							  value_mode);

	cr_assert_eq(CONTENT_OF_ELEMENT(meta_stack->stack)->should_stay_on_stack_a, 1);
	ft_lstclear(&meta_stack->stack, free);
	free(meta_stack);
}

Test(test_markup_all_elements_of_stack, markup_does_not_change_stack)
{
	t_meta_stack	*a = generate_minimal_crash_stack();
	t_meta_stack	*copy = generate_minimal_crash_stack();
	t_list			*markup_reference = calc_markup_reference(a, value_mode);
	t_list			*first_element = a->stack;
	t_list			*last_element = a->last;

	markup_stack_by_reference(a, markup_reference, value_mode);
	count_markups(a->stack);

	cr_assert(ft_lstcompare(a->stack, copy->stack, is_same_value));
	cr_assert(all_prevs_are_properly_set(a));
	cr_assert_eq(first_element, a->stack);
	cr_assert_eq(last_element, a->last);
	ft_lstclear(&a->stack, free);
	free(a);
	ft_lstclear(&copy->stack, free);
	free(copy);
}

Test(test_markup_all_elements_of_stack, index_mode_for_failing_stack)
{
	t_meta_stack	*a = generate_stack_from_str(4, "-19 2 1");
	t_list			*markup_reference = a->stack;
	cr_assert_eq(CONTENT_OF_ELEMENT(markup_reference)->i, -19);

	markup_stack_by_reference(a, markup_reference, index_mode);

	cr_assert(CONTENT_OF_ELEMENT(markup_reference)->should_stay_on_stack_a);
	cr_assert(all_prevs_are_properly_set(a));
	ft_lstclear(&a->stack, free);
	free(a);
}