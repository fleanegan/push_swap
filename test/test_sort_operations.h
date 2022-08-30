#include "test_utils.h"
Test(test_rotate_stack_n_steps, zero_input_does_not_move)
{
	t_meta_stack	*meta_stack = generate_stack_a(3);
	t_list			*first_element = meta_stack->stack;
	rotate_stack_n_steps(meta_stack, 0, NULL);

	cr_assert_eq(meta_stack->stack, first_element);
	ft_lstclear(&meta_stack->stack, free);
	free(meta_stack);
}

Test(test_rotate_stack_n_steps, one_input_does_one_rotation)
{
	t_meta_stack	*meta_stack = generate_stack_a(3);
	t_list			*last_element = meta_stack->last;
	rotate_stack_n_steps(meta_stack, 1, NULL);

	cr_assert_eq(meta_stack->stack, last_element);
	ft_lstclear(&meta_stack->stack, free);
	free(meta_stack);
}

Test(test_rotate_stack_n_steps, minus_one_input_does_one_reverse_rotation)
{
	t_meta_stack	*meta_stack = generate_stack_a(3);
	t_list			*last_element = meta_stack->stack->next;
	rotate_stack_n_steps(meta_stack, -1, NULL);

	cr_assert_eq(meta_stack->stack, last_element);
	ft_lstclear(&meta_stack->stack, free);
	free(meta_stack);
}

Test(test_rotate_stack_n_steps, stack_size_input_rotates_into_init_position)
{
	int				stack_size = 3;
	t_meta_stack	*meta_stack = generate_stack_a(stack_size);
	t_list			*first_element = meta_stack->stack;
	rotate_stack_n_steps(meta_stack, stack_size, NULL);

	cr_assert_eq(meta_stack->stack, first_element);
	ft_lstclear(&meta_stack->stack, free);
	free(meta_stack);
}


Test(test_move_to_top, moving_top_does_nothing)
{
	t_meta_stack	*meta_stack = generate_stack_a(2);
	t_list *next_top = ft_lstget_element_by_index(meta_stack->stack, 0);

	move_to_top(meta_stack, next_top, NULL);

	cr_assert_eq(meta_stack->stack, next_top);
	ft_lstclear(&meta_stack->stack, free);
	free(meta_stack);
}

Test(test_move_to_top, moving_second_element_to_top_will_use_rra)
{
	t_meta_stack	*meta_stack = generate_stack_a(3);
	t_list			*second_element = meta_stack->stack->next;
	t_list			*history = NULL;

	move_to_top(meta_stack, second_element, &history);

	cr_assert_eq(meta_stack->stack, second_element);
	cr_assert_str_eq(history->content, "ra\n");
	ft_lstclear(&meta_stack->stack, free);
	free(meta_stack);
	ft_lstclear(&history, do_not_free_content);
}

Test(test_move_to_top, moving_third_element_to_top_will_use_rrarra)
{
	t_meta_stack	*meta_stack = generate_stack_a(6);
	t_list			*c = ft_lstget_element_by_index(meta_stack->stack, 2);
	t_list			*history = NULL;

	move_to_top(meta_stack, c, &history);

	cr_assert_eq(meta_stack->stack, c);
	cr_assert_str_eq(history->content, "ra\n");
	cr_assert_str_eq(history->next->content, "ra\n");
	ft_lstclear(&meta_stack->stack, free);
	free(meta_stack);
	ft_lstclear(&history, do_not_free_content);
}

Test(test_move_to_top, moving_second_element_to_top_will_use_ra)
{
	t_meta_stack	*meta_stack = generate_stack_a(3);
	t_list			*c = ft_lstget_element_by_index(meta_stack->stack, 1);
	t_list			*history = NULL;

	move_to_top(meta_stack, c, &history);

	cr_assert_eq(meta_stack->stack, c);
	cr_assert_str_eq(history->content, "ra\n");
	ft_lstclear(&meta_stack->stack, free);
	free(meta_stack);
	ft_lstclear(&history, do_not_free_content);
}

Test(test_move_to_top, moving_last_element_to_top_will_use_ra)
{
	t_meta_stack	*meta_stack = generate_stack_a(3);
	t_list			*c = meta_stack->last;
	t_list			*history = NULL;

	move_to_top(meta_stack, c, &history);

	cr_assert_eq(meta_stack->stack, c);
	cr_assert_str_eq(history->content, "rra\n");
	ft_lstclear(&meta_stack->stack, free);
	free(meta_stack);
	ft_lstclear(&history, do_not_free_content);
}

Test(test_calc_moves_to_top, moving_empty_stack_returns_zero)
{
	t_meta_stack	*meta_stack = generate_stack_a(0);
	t_list			*element = ft_lstnew(new_stack_content(1));

	int result = calc_moves_to_top(meta_stack, element);

	cr_assert_eq(result, 0);
	ft_lstclear(&meta_stack->stack, free);
	free(meta_stack);
	ft_lstclear(&element, free);
}


Test(test_calc_moves_to_top, top_element_returns_zero)
{
	t_meta_stack	*meta_stack = generate_stack_a(1);
	t_list			*first_element = meta_stack->stack;

	int result = calc_moves_to_top(meta_stack, first_element);

	cr_assert_eq(result, 0);
	ft_lstclear(&meta_stack->stack, free);
	free(meta_stack);
}

Test(test_calc_moves_to_top, bottom_element_needs_one_move_to_top)
{
	t_meta_stack	*meta_stack = generate_stack_a(3);
	t_list			*last_element = meta_stack->last;

	int result = calc_moves_to_top(meta_stack, last_element);

	cr_assert_eq(result, 1);
	ft_lstclear(&meta_stack->stack, free);
	free(meta_stack);
}

Test(test_calc_moves_to_bottom, top_element_needs_one_move_to_bottom)
{
	t_meta_stack	*meta_stack = generate_stack_a(3);
	t_list			*first_element = meta_stack->stack;

	int result = calc_moves_to_bottom(meta_stack, first_element);

	cr_assert_eq(result, -1);
	ft_lstclear(&meta_stack->stack, free);
	free(meta_stack);
}

Test(test_calc_moves_to_bottom, element_below_top_needs_one_move_to_bottom)
{
	t_meta_stack	*meta_stack = generate_stack_a(3);
	t_list			*second_element = meta_stack->stack->next;

	int result = calc_moves_to_bottom(meta_stack, second_element);

	cr_assert_eq(result, 1);
	ft_lstclear(&meta_stack->stack, free);
	free(meta_stack);
}

Test(test_calc_moves_to_get_a_in_push_position, moving_bigger_element_to_top_is_shortest)
{
	t_meta_stack	*a = generate_test_stack_0(5);
	t_meta_stack	*b = generate_stack_b(0);
	push_first_element_to_the_other_stack(a, b, NULL);
	t_list			*element_to_push = b->stack;

	int result = calc_moves_to_get_a_in_push_position(a, element_to_push);

	cr_assert_eq(result, 1);
	ft_lstclear(&a->stack, free);
	free(a);
	ft_lstclear(&b->stack, free);
	free(b);
}

Test(test_bring_a_in_push_position, pushing_zero_between_neg_and_pos)
{
	t_meta_stack	*a = generate_test_stack_2(5);
	t_meta_stack	*b = generate_stack_b(6);
	t_list	*element_to_push = b->last;

	bring_a_in_push_position(a, element_to_push, NULL);

	cr_assert_eq(get_content_of_element(a->stack)->i, 31);
	ft_lstclear(&a->stack, free);
	free(a);
	ft_lstclear(&b->stack, free);
	free(b);
}

Test(test_calc_moves_to_get_a_in_push_position, works_also_if_a_is_empty)
{
	t_meta_stack	*a = generate_stack_a(0);
	t_meta_stack	*b = generate_stack_b(1);
	t_list	*element_to_push = b->stack;

	int result = calc_moves_to_get_a_in_push_position(a, element_to_push);

	cr_assert_eq(result, 0);
	ft_lstclear(&a->stack, free);
	free(a);
	ft_lstclear(&b->stack, free);
	free(b);
}

Test(test_calc_moves_to_get_a_in_push_position, moving_index_plus_one_to_top_is_shortest)
{
	t_meta_stack	*a = generate_stack_a(2);
	t_meta_stack	*b = generate_stack_b(0);
	push_first_element_to_the_other_stack(a, b, NULL);
	t_list	*element_to_push = b->stack;

	int result = calc_moves_to_get_a_in_push_position(a, element_to_push);

	cr_assert_eq(result, 0);
	ft_lstclear(&a->stack, free);
	free(a);
	ft_lstclear(&b->stack, free);
	free(b);
}

Test(russian_algorithm_move_b_back_to_a, pushing_only_element_if_b_empties_b_and_writes_pa)
{
	t_meta_stack	*a = generate_stack_a(0);
	t_meta_stack	*b = generate_stack_b(1);
	t_list	*history = NULL;

	russian_algorithm_move_b_back_to_a(a, b, &history);

	cr_assert_null(b->stack);
	cr_assert_str_eq(history->content, "pa\n");
	ft_lstclear(&a->stack, free);
	free(a);
	ft_lstclear(&b->stack, free);
	free(b);
	ft_lstclear(&history, do_not_free_content);
}

Test(russian_algorithm_move_b_back_to_a, after_call_b_is_empty)
{
	t_meta_stack	*a = generate_stack_a(0);
	t_meta_stack	*b = generate_stack_b(4);
	t_list	*history = NULL;

	russian_algorithm_move_b_back_to_a(a, b, &history);

	cr_assert_null(b->stack);
	ft_lstclear(&a->stack, free);
	free(a);
	ft_lstclear(&b->stack, free);
	free(b);
	ft_lstclear(&history, do_not_free_content);
}

Test(rotate_a_back_in_order, simple_test_all_checks_already_covered)
{
	t_meta_stack	*a = generate_stack_a(3);
	t_list *history = NULL;
	reverse_rotate(a, NULL);

	rotate_a_back_in_order(a, &history);

	cr_assert_eq(get_content_of_element(a->stack)->i, 0);
	ft_lstclear(&a->stack, free);
	free(a);
	ft_lstclear(&history, do_not_free_content);
}
