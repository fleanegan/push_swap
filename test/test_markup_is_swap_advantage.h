#include "test_utils.h"

Test(test_markup_is_swap_advantage, yes)
{
	t_meta_stack	*a = generate_test_stack_0();
	t_list	*markup_reference = calc_markup_reference(a, value_mode);
	rotate(a, NULL);

	int	result = is_swapping_a_good_idea(a, markup_reference, value_mode);

	cr_assert(result);
	ft_lstclear(&a->stack, free);
	free(a);
}

Test(test_markup_is_swap_advantage, markup_is_the_same_before_and_after)
{
	t_meta_stack	*a = generate_test_stack_1();
	t_list			*saved_element = a->stack;
	t_list			*markup_reference = calc_markup_reference(a, value_mode);
	markup_stack_by_reference(a, markup_reference, value_mode);
	int		should_saved_element_stay_before = get_content_of_element(
			saved_element)->should_stay_on_stack_a;

	int	result = is_swapping_a_good_idea(a, markup_reference, value_mode);

	int		should_saved_element_stay_after = get_content_of_element(
			saved_element)->should_stay_on_stack_a;
	cr_assert_eq(should_saved_element_stay_before, should_saved_element_stay_after, "bef %d, after %d", should_saved_element_stay_before, should_saved_element_stay_after);
	cr_assert(result);
	ft_lstclear(&a->stack, free);
	free(a);
}

Test(test_markup_is_swap_advantage, if_both_elements_are_allowed_to_stay_do_nothing_and_return_false)
{
	t_meta_stack	*a = generate_test_stack_2();
	t_list			*markup_reference = calc_markup_reference(a, value_mode);
	markup_stack_by_reference(a, markup_reference, value_mode);

	int	result = is_swapping_a_good_idea(a, markup_reference, value_mode);

	cr_assert(! result);
	ft_lstclear(&a->stack, free);
	free(a);
}

Test(test_markup_is_swap_advantage, recalculates)
{
	t_meta_stack	*a = generate_test_stack_2();
	t_list			*saved_element = a->stack;
	t_list			*markup_reference = calc_markup_reference(a, value_mode);
	int				should_saved_element_stay_before = 0;
	get_content_of_element(saved_element)->should_stay_on_stack_a = should_saved_element_stay_before;

	markup_stack_by_reference(a, markup_reference, value_mode);
	int	result = is_swapping_a_good_idea(a, markup_reference, value_mode);

	int		should_saved_element_stay_after = get_content_of_element(
			saved_element)->should_stay_on_stack_a;
	cr_assert(should_saved_element_stay_after, "bef %d, after %d", should_saved_element_stay_before, should_saved_element_stay_after);
	cr_assert(! result);
	ft_lstclear(&a->stack, free);
	free(a);
}

Test(test_markup_is_swap_advantaged, no)
{
	t_meta_stack	*a = generate_test_stack_0();
	t_list			*markup_reference = calc_markup_reference(a, value_mode);
	rotate(a, NULL);
	swap_first_two_elements(a, NULL);
	markup_stack_by_reference(a, markup_reference, value_mode);

	int	result = is_swapping_a_good_idea(a, markup_reference, value_mode);

	cr_assert(! result);
	ft_lstclear(&a->stack, free);
	free(a);
}

Test(test_markup_is_swap_advantaged, check_does_not_alter_stack_order)
{
	t_meta_stack	*a = generate_test_stack_0();
	t_list			*markup_reference = calc_markup_reference(a, value_mode);
	rotate(a, NULL);
	t_list 			*first_element = a->stack->next;

	is_swapping_a_good_idea(a, markup_reference, value_mode);

	cr_assert_eq(a->stack->next, first_element);
	ft_lstclear(&a->stack, free);
	free(a);
}

Test(test_markup_is_swap_advantaged, swap_failure_stack_index_mode)
{
	t_meta_stack	*a = generate_stack_from_str(4, "0 2 1");
	t_list			*markup_reference = calc_markup_reference(a, index_mode);
	cr_assert_eq(a->stack, markup_reference);
	markup_stack_by_reference(a, markup_reference, index_mode);

	cr_assert(is_swapping_a_good_idea(a, markup_reference, index_mode));
	ft_lstclear(&a->stack, free);
	free(a);
}

Test(test_markup_is_swap_advantaged, checking_bug_stack_does_no)
{
	t_meta_stack	*a = generate_loop_bug_stack();
	t_list			*markup_reference = a->stack->next;
	cr_assert_eq(get_content_of_element(markup_reference)->i, 1, "act %d",
				 get_content_of_element(markup_reference)->i);

	markup_stack_by_reference(a, markup_reference, value_mode);
	int				before_is_swapping = count_markups(a->stack);
	int 			top_should_stay_after = get_content_of_element(a->stack)->should_stay_on_stack_a;

	is_swapping_a_good_idea(a, markup_reference, value_mode);
	int				after_is_swapping = count_markups(a->stack);
	int 			top_should_stay_before = get_content_of_element(a->stack)->should_stay_on_stack_a;

	cr_assert_eq(before_is_swapping, after_is_swapping, "elem to b bef: %d ,after: %d", before_is_swapping, after_is_swapping);
	cr_assert_eq(top_should_stay_after, top_should_stay_before);
	ft_lstclear(&a->stack, free);
	free(a);
}