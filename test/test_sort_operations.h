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
