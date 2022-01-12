#include "test_utils.h"

Test(calc_total_steps_to_move_given_element_from_b_to_top_a, simplest_case)
{
	t_list	*a = generate_stack_a(3);
	t_list	*b = NULL;
	push_first_element_of_a_to_b(&a, &b, NULL);
	t_list	*push_candidate = b;

	int res_act = calc_moves_to_push_element_onto_a(a, b, push_candidate);

	cr_assert_eq(res_act, 1);
	ft_lstclear(&a, free);
	ft_lstclear(&b, free);
}

Test(calc_total_steps_to_move_given_element_from_b_to_top_a, need_to_rotate_b)
{
	t_list	*a = generate_stack_a(4);
	t_list	*b = NULL;
	push_first_element_of_a_to_b(&a, &b, NULL);
	push_first_element_of_a_to_b(&a, &b, NULL);
	t_list	*push_candidate = ft_lstlast(b);

	int res_act = calc_moves_to_push_element_onto_a(a, b, push_candidate);

	cr_assert_eq(res_act, 2, "act %d", res_act);
	ft_lstclear(&a, free);
	ft_lstclear(&b, free);
}

Test(find_element_with_minimal_steps_to_push_to_a, need_to_rotate_b)
{
	t_list	*a = generate_stack_a(4);
	t_list	*b = NULL;
	push_first_element_of_a_to_b(&a, &b, NULL);
	push_first_element_of_a_to_b(&a, &b, NULL);
	t_list	*push_candidate = ft_lstlast(b);

	int res_act = calc_moves_to_push_element_onto_a(a, b, push_candidate);

	cr_assert_eq(res_act, 2, "act %d", res_act);
	ft_lstclear(&a, free);
	ft_lstclear(&b, free);
}