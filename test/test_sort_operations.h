#include "test_utils.h"

Test(test_calc_direction_to_top, returns_zero_if_already_on_top)
{
	t_list *stack = generate_stack_a(1);
	t_list *a = ft_lstget_element_by_index(stack, 0);

	int		direction = calc_direction_to_top(stack, a);

	cr_assert_eq(direction, 0);
	ft_lstclear(&stack, free);
}

Test(test_calc_direction_to_top, returns_negative_if_above_half)
{
	t_list *stack = generate_stack_a(20);
	t_list *b = ft_lstget_element_by_index(stack, 4);

	int		direction = calc_direction_to_top(stack, b);

	cr_assert_eq(direction, -1);
	ft_lstclear(&stack, free);
}

Test(test_calc_direction_to_top, returns_negative_if_on_half)
{
	t_list *stack = generate_stack_a(2);
	t_list *b = ft_lstget_element_by_index(stack, 1);

	int		direction = calc_direction_to_top(stack, b);

	cr_assert_eq(direction, -1);
	ft_lstclear(&stack, free);
}

Test(test_calc_direction_to_top, returns_positive_if_after_half)
{
	t_list *stack = generate_stack_a(3);
	t_list *c = ft_lstget_element_by_index(stack, 2);

	int		direction = calc_direction_to_top(stack, c);

	cr_assert_eq(direction, 1);
	ft_lstclear(&stack, free);
}

Test(test_move_to_top, moving_top_does_nothing)
{
	t_list *stack = generate_stack_a(2);
	t_list *a = ft_lstget_element_by_index(stack, 0);

	move_to_top(&stack, a, NULL);

	cr_assert_eq(stack, a);
	ft_lstclear(&stack, free);
}

Test(test_move_to_top, moving_second_element_to_top_will_use_rra)
{
	t_list	*stack = generate_stack_a(3);
	t_list	*b = ft_lstget_element_by_index(stack, 1);
	t_list	*history = NULL;

	move_to_top(&stack, b, &history);

	cr_assert_eq(stack, b);
	cr_assert_str_eq(history->content, "rra\n");
	ft_lstclear(&stack, free);
	ft_lstclear(&history, do_not_free_content);
}

Test(test_move_to_top, moving_third_element_to_top_will_use_rrarra)
{
	t_list	*stack = generate_stack_a(6);
	t_list	*c = ft_lstget_element_by_index(stack, 2);
	t_list	*history = NULL;

	move_to_top(&stack, c, &history);

	cr_assert_eq(stack, c);
	cr_assert_str_eq(history->content, "rra\n");
	cr_assert_str_eq(history->next->content, "rra\n");
	ft_lstclear(&stack, free);
	ft_lstclear(&history, do_not_free_content);
}

Test(test_move_to_top, moving_second_element_to_top_will_use_ra)
{
	t_list	*stack = generate_stack_a(3);
	t_list	*c = ft_lstget_element_by_index(stack, 2);
	t_list	*history = NULL;

	move_to_top(&stack, c, &history);

	cr_assert_eq(stack, c);
	cr_assert_str_eq(history->content, "ra\n");
	ft_lstclear(&stack, free);
	ft_lstclear(&history, do_not_free_content);
}

Test(test_calc_moves_to_top, moving_empty_stack_returns_zero)
{
	t_list	*stack = NULL;
	t_list	*element = stack;

	int result = calc_moves_to_top(stack, element);

	cr_assert_eq(result, 0);
	ft_lstclear(&stack, free);
}

Test(test_calc_moves_to_top, empty_element_returns_minus_one)
{
	t_list	*stack = generate_stack_a(1);
	t_list	*element = NULL;

	int result = calc_moves_to_top(stack, element);

	cr_assert_eq(result, -1);
	ft_lstclear(&stack, free);
}


Test(test_calc_moves_to_top, element_not_in_stack_returns_minus_one)
{
	t_list	*stack = generate_stack_a(1);
	t_list	*element = generate_stack_b(1);

	int result = calc_moves_to_top(stack, element);

	cr_assert_eq(result, -1);
	ft_lstclear(&stack, free);
}

Test(test_calc_moves_to_top, top_element_returns_zero)
{
	t_list	*stack = generate_stack_a(1);
	t_list	*element = stack;

	int result = calc_moves_to_top(stack, element);

	cr_assert_eq(result, 0);
	ft_lstclear(&stack, free);
}

Test(test_calc_moves_to_top, bottom_element_needs_one_move_to_top)
{
	t_list	*stack = generate_stack_a(3);
	t_list	*element = ft_lstlast(stack);

	int result = calc_moves_to_top(stack, element);

	cr_assert_eq(result, 1);
	ft_lstclear(&stack, free);
}

Test(test_calc_moves_to_bottom, top_element_needs_one_move_to_bottom)
{
	t_list	*stack = generate_stack_a(3);
	t_list	*element = stack;

	int result = calc_moves_to_bottom(stack, element);

	cr_assert_eq(result, 1);
	ft_lstclear(&stack, free);
}

Test(test_calc_moves_to_bottom, element_above_top_needs_one_move_to_bottom)
{
	t_list	*stack = generate_stack_a(3);
	t_list	*element = stack->next;

	int result = calc_moves_to_bottom(stack, element);

	cr_assert_eq(result, 1);
	ft_lstclear(&stack, free);
}

Test(test_calc_moves_to_get_a_in_push_position, move_index_minus_one_to_top_is_shortest)
{
	t_list	*a = generate_test_stack_0(5);
	t_list	*b = NULL;
	push_first_element_of_a_to_b(&a, &b, NULL);
	t_list	*element_to_push = b;

	int result = calc_moves_to_get_a_in_push_position(a, element_to_push);

	cr_assert_eq(result, 1);
	ft_lstclear(&a, free);
	ft_lstclear(&b, free);
}

Test(test_calc_moves_to_get_a_in_push_position, moving_index_plus_one_to_top_is_shortest)
{
	t_list	*a = generate_stack_a(4);
	t_list	*b = NULL;
	push_first_element_of_a_to_b(&a, &b, NULL);
	t_list	*element_to_push = b;

	int result = calc_moves_to_get_a_in_push_position(a, element_to_push);

	cr_assert_eq(result, 0);
	ft_lstclear(&a, free);
	ft_lstclear(&b, free);
}