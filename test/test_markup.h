#include "test_utils.h"

Test(test_markup_single_element, with_higher_number_stays_on_list)
{
	t_list	*stack = generate_stack_a(2);
	t_list	*reference = stack;
	int		global_max = INT_MIN;
	t_list	*element_to_be_marked_up = stack->next;

	markup_one_element(reference, element_to_be_marked_up, &global_max);

	cr_assert_eq(CONTENT_OF_ELEMENT(element_to_be_marked_up)->should_stay_on_stack_a, 1);
	ft_lstclear(&stack, free);
}

Test(test_markup_single_element, updates_global_max)
{
	t_list	*stack = generate_stack_a(2);
	t_list	*reference = stack;
	int		global_max = INT_MIN;
	t_list	*element_to_be_marked_up = stack->next;

	markup_one_element(reference, element_to_be_marked_up, &global_max);

	cr_assert_eq(global_max, 1);
	ft_lstclear(&stack, free);
}

Test(test_markup_single_element, with_higher_number_does_not_stay_on_list_if_below_global_max)
{
	t_list	*stack = generate_stack_a(2);
	t_list	*reference = stack;
	int		global_max = INT_MAX;
	t_list	*element_to_be_marked_up = stack->next;

	markup_one_element(reference, element_to_be_marked_up, &global_max);

	cr_assert_eq(CONTENT_OF_ELEMENT(element_to_be_marked_up)->should_stay_on_stack_a, 0);
	ft_lstclear(&stack, free);
}

Test(test_markup_count_for_element, count_equals_to_elements_greater_or_equal_to_head_of_stack)
{
	t_list	*stack = generate_test_stack_0();
	markup_all_elements_according_to_reference(stack, stack);

	int number_of_elements_which_stay_on_a = count_markups(stack);

	cr_assert_eq(number_of_elements_which_stay_on_a, 2);
	ft_lstclear(&stack, free);
}

Test(test_markup, do_nothing_if_empty)
{
	t_list *stack = NULL;
	t_list *res_exp = stack;

	t_list	*markup_reference = calc_markup_reference(stack);

	cr_assert_eq(markup_reference, res_exp);
}

Test(test_markup, calc_markup_reference)
{
	t_list *stack = generate_test_stack_0();
	t_list *res_exp = ft_lstget_element_by_index(stack, 2);

	t_list	*markup_reference = calc_markup_reference(stack);

	cr_assert_eq(markup_reference, res_exp);
	ft_lstclear(&stack, free);
}

Test(test_markup, use_first_element_if_only_one_exists)
{
	t_list *stack = ft_lstnew(new_stack_content(0));
	t_list *res_exp = stack;

	t_list	*markup_reference = calc_markup_reference(stack);

	cr_assert_eq(markup_reference, res_exp);
	ft_lstclear(&stack, free);
}

Test(test_markup, complex_stack)
{
	t_list *stack = generate_test_stack_2();
	t_list	*markup_reference = calc_markup_reference(stack);

	markup_all_elements_according_to_reference(stack, markup_reference);

	cr_assert_eq(CONTENT_OF_ELEMENT(stack)->should_stay_on_stack_a, 1);
	ft_lstclear(&stack, free);
}

Test(test_markup, markup_elements_does_nothing_if_candidate_not_in_a)
{
	t_list *stack = generate_stack_b(2);
	t_list	*markup_reference = stack;
	CONTENT_OF_ELEMENT(markup_reference)->is_on_stack_a = 0;

	markup_all_elements_according_to_reference(stack, markup_reference);

	cr_assert_eq(CONTENT_OF_ELEMENT(markup_reference)->should_stay_on_stack_a, 0);
	ft_lstclear(&stack, free);
}

Test(test_markup, markup_elements)
{
	t_list *stack = generate_test_stack_0();
	t_list	*markup_reference = calc_markup_reference(stack);
	markup_all_elements_according_to_reference(stack, markup_reference);

	count_markups(stack);

	int	markup_count = count_markups(stack);

	cr_assert_eq(markup_count, 3, "markupcount %d", markup_count);
	ft_lstclear(&stack, free);
}

Test(test_markup, markup_list_with_one_element)
{
	t_list *stack = ft_lstnew(new_stack_content(0));
	markup_all_elements_according_to_reference(stack, stack);
	count_markups(stack);

	int	markup_count = count_markups(stack);

	cr_assert_eq(markup_count, 1, "markupcount %d", markup_count);
	ft_lstclear(&stack, free);
}

Test(test_markup, markup_complex_list)
{
	t_list *stack = generate_test_stack_2();
	t_list *reference = calc_markup_reference(stack);
	t_list *first_element = stack;
	markup_all_elements_according_to_reference(stack, reference);

	cr_assert(CONTENT_OF_ELEMENT(first_element)->should_stay_on_stack_a);
	ft_lstclear(&stack, free);
}

Test(test_markup, markup_does_not_change_stack)
{
	t_list	*stack = generate_test_stack_0();
	t_list	*copy = generate_test_stack_0();
	t_list	*markup_reference = calc_markup_reference(stack);
	markup_all_elements_according_to_reference(stack, markup_reference);

	count_markups(stack);

	cr_assert(ft_lstcompare(stack, copy, is_same_value));
	ft_lstclear(&stack, free);
	ft_lstclear(&copy, free);
}

Test(test_markup_is_swapping_a_good_idea, yes)
{
	t_list 	*stack = generate_test_stack_0();
	t_list	*markup_reference = calc_markup_reference(stack);
	reverse_rotate(&stack, NULL);

	int	result = is_swapping_a_good_idea(stack, markup_reference);

	cr_assert(result);
	ft_lstclear(&stack, free);
}

Test(test_markup_is_swapping_a_good_idea, markup_is_the_same_before_and_after)
{
	t_list 	*stack = generate_test_stack_1();
	t_list	*saved_element = stack;
	t_list	*markup_reference = calc_markup_reference(stack);
	markup_all_elements_according_to_reference(stack, markup_reference);
	int		should_saved_element_stay_before = CONTENT_OF_ELEMENT(saved_element)->should_stay_on_stack_a;

	int	result = is_swapping_a_good_idea(stack, markup_reference);

	int		should_saved_element_stay_after = CONTENT_OF_ELEMENT(saved_element)->should_stay_on_stack_a;

	cr_assert_neq(should_saved_element_stay_before, should_saved_element_stay_after, "bef %d, after %d", should_saved_element_stay_before, should_saved_element_stay_after);
	cr_assert(result);
	ft_lstclear(&stack, free);
}

Test(test_markup_is_swapping_a_good_idea, if_both_elements_are_allowed_to_stay_do_nothing_and_return_false)
{
	t_list 	*stack = generate_test_stack_2();
	t_list	*markup_reference = calc_markup_reference(stack);
	markup_all_elements_according_to_reference(stack, markup_reference);

	int	result = is_swapping_a_good_idea(stack, markup_reference);

	cr_assert(! result);
	ft_lstclear(&stack, free);
}

Test(test_markup_is_swapping_a_good_idea, recalculates)
{
	t_list 	*stack = generate_test_stack_2();
	t_list	*saved_element = stack;
	t_list	*markup_reference = calc_markup_reference(stack);
	CONTENT_OF_ELEMENT(saved_element)->should_stay_on_stack_a = 0;
	int		should_saved_element_stay_before = CONTENT_OF_ELEMENT(saved_element)->should_stay_on_stack_a;

	int	result = is_swapping_a_good_idea(stack, markup_reference);

	int		should_saved_element_stay_after = CONTENT_OF_ELEMENT(saved_element)->should_stay_on_stack_a;

	cr_assert(should_saved_element_stay_after, "bef %d, after %d", should_saved_element_stay_before, should_saved_element_stay_after);
	cr_assert(! result);
	ft_lstclear(&stack, free);
}

Test(test_markup_is_swapping_a_good_idead, no)
{
	t_list 	*stack = generate_test_stack_0();
	t_list	*markup_reference = calc_markup_reference(stack);
	reverse_rotate(&stack, NULL);
	swap_first_two_elements(&stack, NULL);
	markup_all_elements_according_to_reference(stack, markup_reference);

	int	result = is_swapping_a_good_idea(stack, markup_reference);

	cr_assert(! result);
	ft_lstclear(&stack, free);
}

Test(test_markup_is_swapping_a_good_idead, check_does_not_alter_stack_order)
{
	t_list 	*stack = generate_test_stack_0();
	t_list	*markup_reference = calc_markup_reference(stack);
	reverse_rotate(&stack, NULL);
	t_list 	*first_element = stack->next;

	is_swapping_a_good_idea(stack, markup_reference);

	cr_assert_eq(stack->next, first_element);
	ft_lstclear(&stack, free);
}

Test(test_count_elements_to_be_moved_to_b, no_one_stays_in_a)
{
	t_list 	*stack = generate_stack_a(3);
	mark_stack_as_stay_on_a(stack, 0);

	int result = count_elements_to_be_moved_to_b(stack);

	cr_assert_eq(result, 3);
	ft_lstclear(&stack, free);
}
