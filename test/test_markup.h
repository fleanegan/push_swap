#include "test_utils.h"

Test(test_markup_single_element, with_higher_number_stays_on_list)
{
	t_meta_stack	*meta_stack = generate_stack_a(2);
	t_list			*reference = meta_stack->stack;
	int				global_max = INT_MIN;
	t_list	*element_to_be_marked_up = meta_stack->stack->next;

	markup_one_element(reference, element_to_be_marked_up, &global_max);

	cr_assert_eq(CONTENT_OF_ELEMENT(element_to_be_marked_up)->should_stay_on_stack_a, 1);
	ft_lstclear(&meta_stack->stack, free);
	free(meta_stack);
}

Test(test_markup_single_element, updates_global_max)
{
	t_meta_stack	*meta_stack = generate_stack_a(2);
	t_list			*reference = meta_stack->stack;
	int				global_max = INT_MIN;
	t_list	*element_to_be_marked_up = meta_stack->stack->next;

	markup_one_element(reference, element_to_be_marked_up, &global_max);

	cr_assert_eq(global_max, 1);
	ft_lstclear(&meta_stack->stack, free);
	free(meta_stack);
}

Test(test_markup_single_element, with_higher_number_does_not_stay_on_list_if_below_global_max)
{
	t_meta_stack	*meta_stack = generate_stack_a(2);
	t_list			*reference = meta_stack->stack;
	int				global_max = INT_MAX;
	t_list	*element_to_be_marked_up = meta_stack->stack->next;

	markup_one_element(reference, element_to_be_marked_up, &global_max);

	cr_assert_eq(CONTENT_OF_ELEMENT(element_to_be_marked_up)->should_stay_on_stack_a, 0);
	ft_lstclear(&meta_stack->stack, free);
	free(meta_stack);
}

Test(test_markup_count_for_element, count_equals_to_elements_greater_or_equal_to_head_of_stack)
{
	t_meta_stack	*meta_stack = generate_test_stack_0();
	markup_all_elements_according_to_reference(meta_stack, meta_stack->stack);

	int number_of_elements_which_stay_on_a = count_markups(meta_stack->stack);

	cr_assert_eq(number_of_elements_which_stay_on_a, 2);
	ft_lstclear(&meta_stack->stack, free);
	free(meta_stack);
}

Test(test_markup, on_ascending_stack_reference_is_smallest_number)
{
	t_meta_stack	*a = generate_stack_a(2);

	t_list			*markup_reference = calc_markup_reference(a, value_mode);

	cr_assert_eq(markup_reference, a->stack);
	ft_lstclear(&a->stack, free);
	free(a);
}

Test(test_markup, calc_markup_reference)
{
	t_meta_stack	*meta_stack = generate_test_stack_0();
	t_list *res_exp = ft_lstget_element_by_index(meta_stack->stack, 2);

	t_list	*markup_reference = calc_markup_reference(meta_stack, value_mode);;

	cr_assert_eq(markup_reference, res_exp, "act %d", CONTENT_OF_ELEMENT(markup_reference)->i);
	ft_lstclear(&meta_stack->stack, free);
	free(meta_stack);
}

Test(test_markup, use_first_element_if_only_one_exists)
{
	t_meta_stack	*meta_stack = generate_stack_a(1);
	t_list *res_exp = meta_stack->stack;

	t_list	*markup_reference = calc_markup_reference(meta_stack, value_mode);;

	cr_assert_eq(markup_reference, res_exp);
	ft_lstclear(&meta_stack->stack, free);
	free(meta_stack);
}

Test(test_markup, complex_stack)
{
	t_meta_stack	*meta_stack = generate_test_stack_2();
	t_list	*markup_reference = calc_markup_reference(meta_stack, value_mode);;

	markup_all_elements_according_to_reference(meta_stack, markup_reference);

	cr_assert_eq(CONTENT_OF_ELEMENT(meta_stack->stack)->should_stay_on_stack_a, 1);
	ft_lstclear(&meta_stack->stack, free);
	free(meta_stack);
}

/*// TODO: is this really relevant after torvalds lists
Test(test_markup, markup_elements_does_nothing_if_candidate_not_in_a)
{
	t_meta_stack *b = generate_stack_b(2);
	t_list	*markup_reference = b->stack;
	CONTENT_OF_ELEMENT(markup_reference)->is_on_stack_a = 0;

	markup_all_elements_according_to_reference(stack, markup_reference);

	cr_assert_eq(CONTENT_OF_ELEMENT(markup_reference)->should_stay_on_stack_a, 0);
	ft_lstclear(&stack, free);
}*/

Test(test_markup, markup_elements)
{
	t_meta_stack	*a = generate_test_stack_0();
	t_list	*markup_reference = calc_markup_reference(a, value_mode);
	markup_all_elements_according_to_reference(a, markup_reference);

	int	markup_count = count_markups(a->stack);

	cr_assert_eq(markup_count, 3, "markupcount %d", markup_count);
	ft_lstclear(&a->stack, free);
	free(a);
}

Test(test_markup, markup_list_with_one_element)
{
	t_meta_stack	*a = generate_stack_a(1);
	markup_all_elements_according_to_reference(a, a->stack);

	int	markup_count = count_markups(a->stack);

	cr_assert_eq(markup_count, 1, "markupcount %d", markup_count);
	ft_lstclear(&a->stack, free);
	free(a);
}

Test(test_markup, markup_complex_list)
{
	t_meta_stack	*a = generate_test_stack_2();
	t_list *reference = calc_markup_reference(a, value_mode);
	t_list *first_element = a->stack;
	markup_all_elements_according_to_reference(a, reference);

	cr_assert(CONTENT_OF_ELEMENT(first_element)->should_stay_on_stack_a);
	ft_lstclear(&a->stack, free);
	free(a);
}

Test(test_markup, markup_does_not_change_stack)
{
	t_meta_stack	*a = generate_minimal_crash_stack();
	t_meta_stack	*copy = generate_minimal_crash_stack();
	t_list			*markup_reference = calc_markup_reference(a, value_mode);
	t_list			*first_element = a->stack;
	t_list			*last_element = a->last;

	markup_all_elements_according_to_reference(a, markup_reference);
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

Test(test_markup_is_swapping_a_good_idea, yes)
{
	t_meta_stack	*a = generate_test_stack_0();
	t_list	*markup_reference = calc_markup_reference(a, value_mode);
	reverse_rotate(a, NULL);

	int	result = is_swapping_a_good_idea(a, markup_reference);

	cr_assert(result);
	ft_lstclear(&a->stack, free);
	free(a);
}

Test(test_markup_is_swapping_a_good_idea, markup_is_the_same_before_and_after)
{
	t_meta_stack	*a = generate_test_stack_1();
	t_list			*saved_element = a->stack;
	t_list			*markup_reference = calc_markup_reference(a, value_mode);
	markup_all_elements_according_to_reference(a, markup_reference);
	int		should_saved_element_stay_before = CONTENT_OF_ELEMENT(saved_element)->should_stay_on_stack_a;

	int	result = is_swapping_a_good_idea(a, markup_reference);

	int		should_saved_element_stay_after = CONTENT_OF_ELEMENT(saved_element)->should_stay_on_stack_a;
	cr_assert_eq(should_saved_element_stay_before, should_saved_element_stay_after, "bef %d, after %d", should_saved_element_stay_before, should_saved_element_stay_after);
	cr_assert(result);
	ft_lstclear(&a->stack, free);
	free(a);
}

Test(test_markup_is_swapping_a_good_idea, if_both_elements_are_allowed_to_stay_do_nothing_and_return_false)
{
	t_meta_stack	*a = generate_test_stack_2();
	t_list			*markup_reference = calc_markup_reference(a, value_mode);
	markup_all_elements_according_to_reference(a, markup_reference);

	int	result = is_swapping_a_good_idea(a, markup_reference);

	cr_assert(! result);
	ft_lstclear(&a->stack, free);
	free(a);
}

Test(test_markup_is_swapping_a_good_idea, recalculates)
{
	t_meta_stack	*a = generate_test_stack_2();
	t_list			*saved_element = a->stack;
	t_list			*markup_reference = calc_markup_reference(a, value_mode);
	int				should_saved_element_stay_before = 0;
	CONTENT_OF_ELEMENT(saved_element)->should_stay_on_stack_a = should_saved_element_stay_before;

	markup_all_elements_according_to_reference(a, markup_reference);
	int	result = is_swapping_a_good_idea(a, markup_reference);

	int		should_saved_element_stay_after = CONTENT_OF_ELEMENT(saved_element)->should_stay_on_stack_a;
	cr_assert(should_saved_element_stay_after, "bef %d, after %d", should_saved_element_stay_before, should_saved_element_stay_after);
	cr_assert(! result);
	ft_lstclear(&a->stack, free);
	free(a);
}

Test(test_markup_is_swapping_a_good_idead, no)
{
t_meta_stack	*a = generate_test_stack_0();
t_list			*markup_reference = calc_markup_reference(a, value_mode);
reverse_rotate(a, NULL);
swap_first_two_elements(a, NULL);
markup_all_elements_according_to_reference(a, markup_reference);

int	result = is_swapping_a_good_idea(a, markup_reference);

cr_assert(! result);
ft_lstclear(&a->stack, free);
free(a);
}

Test(test_markup_is_swapping_a_good_idead, check_does_not_alter_stack_order)
{
	t_meta_stack	*a = generate_test_stack_0();
	t_list			*markup_reference = calc_markup_reference(a, value_mode);
	reverse_rotate(a, NULL);
	t_list 			*first_element = a->stack->next;

	is_swapping_a_good_idea(a, markup_reference);

	cr_assert_eq(a->stack->next, first_element);
	ft_lstclear(&a->stack, free);
	free(a);
}

Test(test_markup_is_swapping_a_good_idead, checking_bug_stack_does_no)
{
	t_meta_stack	*a = generate_loop_bug_stack();
	t_list			*markup_reference = a->stack->next;
	cr_assert_eq(CONTENT_OF_ELEMENT(markup_reference)->i, 1, "act %d", CONTENT_OF_ELEMENT(markup_reference)->i);

	markup_all_elements_according_to_reference(a, markup_reference);
	int				before_is_swapping = count_elements_to_be_moved_to_b(a->stack);
	int 			top_should_stay_after = CONTENT_OF_ELEMENT(a->stack)->should_stay_on_stack_a;

					is_swapping_a_good_idea(a, markup_reference);
	int				after_is_swapping = count_elements_to_be_moved_to_b(a->stack);
	int 			top_should_stay_before = CONTENT_OF_ELEMENT(a->stack)->should_stay_on_stack_a;

	cr_assert_eq(before_is_swapping, after_is_swapping, "elem to b bef: %d ,after: %d", before_is_swapping, after_is_swapping);
	cr_assert_eq(top_should_stay_after, top_should_stay_before);
	ft_lstclear(&a->stack, free);
	free(a);
}

Test(test_count_elements_to_be_moved_to_b, no_one_stays_in_a)
{
	t_meta_stack	*a = generate_stack_a(3);
	mark_stack_as_stay_on_a(a->stack, 0);

	int result = count_elements_to_be_moved_to_b(a->stack);

	cr_assert_eq(result, 3);
	ft_lstclear(&a->stack, free);
	free(a);
}
