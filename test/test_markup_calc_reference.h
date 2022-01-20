#include "test_utils.h"

Test(test_markup_calc_reference, on_ascending_stack_reference_is_smallest_number)
{
t_meta_stack	*a = generate_stack_a(2);

t_list			*markup_reference = calc_markup_reference(a, value_mode);

cr_assert_eq(markup_reference, a->stack);
ft_lstclear(&a->stack, free);
free(a);
}

Test(test_markup_calc_reference, calc_markup_reference)
{
t_meta_stack	*meta_stack = generate_test_stack_0();
t_list *res_exp = ft_lstget_element_by_index(meta_stack->stack, 2);

t_list	*markup_reference = calc_markup_reference(meta_stack, value_mode);;

cr_assert_eq(markup_reference, res_exp, "act %d", CONTENT_OF_ELEMENT(markup_reference)->i);
ft_lstclear(&meta_stack->stack, free);
free(meta_stack);
}

Test(test_markup_calc_reference, use_first_element_if_only_one_exists)
{
	t_meta_stack	*meta_stack = generate_stack_a(1);
	t_list *res_exp = meta_stack->stack;

	t_list	*markup_reference = calc_markup_reference(meta_stack, value_mode);;

	cr_assert_eq(markup_reference, res_exp);
	ft_lstclear(&meta_stack->stack, free);
	free(meta_stack);
}

Test(test_markup_calc_reference, use_index_markup_mode)
{
	t_meta_stack	*meta_stack = generate_test_stack_0();
	t_list *res_exp = meta_stack->stack->next->next;

	t_list	*markup_reference = calc_markup_reference(meta_stack, index_mode);

	cr_assert_eq(markup_reference, res_exp, "exp: %d, got %d",
				 CONTENT_OF_ELEMENT(res_exp)->i, CONTENT_OF_ELEMENT(markup_reference)->i);
	ft_lstclear(&meta_stack->stack, free);
	free(meta_stack);
}

Test(test_markup_calc_reference, calc_markup_reference_for_faililng_case)
{
	t_meta_stack	*meta_stack = generate_stack_from_str(4, "-19 2 1");
	t_list *res_exp = meta_stack->stack;

	t_list	*markup_reference = calc_markup_reference(meta_stack, index_mode);;

	cr_assert_eq(markup_reference, res_exp, "act %d", CONTENT_OF_ELEMENT(markup_reference)->i);
	ft_lstclear(&meta_stack->stack, free);
	free(meta_stack);
}
