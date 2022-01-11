#include "test_utils.h"

Test(test_stack_operations, pushing_from_empty_stack_does_noting, .disabled=0)
{
	t_list **a = NULL;
	t_list **b = NULL;

	push_first_element_of_a_to_b(a, b, NULL);
}

Test(test_stack_operations, pushing_from_a_puts_element_in_front_of_b, .disabled=0)
{
	t_list *a = generate_stack_a(1);
	t_list *b = NULL;

	push_first_element_of_a_to_b(&a, &b, NULL);

	cr_assert_eq(CONTENT_OF_ELEMENT(b)->index, 0);
	ft_lstclear(&a, free);
	ft_lstclear(&b, free);
}

Test(test_stack_operations, pushing_updates_history_list, .disabled=0)
{
	t_list	*a = generate_stack_a(1);
	t_list	*b = NULL;
	t_list	*history = NULL;

	push_first_element_of_a_to_b(&a, &b, &history);

	cr_assert_str_eq(history->content, "pb\n");
	ft_lstclear(&a, free);
	ft_lstclear(&b, free);
	ft_lstclear(&history, do_not_free_content);
}

Test(test_stack_operations, pushing_from_b_writes_pa_in_history_list, .disabled=0)
{
	t_list	*a = NULL;
	t_list	*b = generate_stack_b(1);
	t_list	*history = NULL;

	push_first_element_of_a_to_b(&b, &a, &history);

	cr_assert_str_eq(history->content, "pa\n");
	ft_lstclear(&a, free);
	ft_lstclear(&b, free);
	ft_lstclear(&history, do_not_free_content);
}

Test(test_stack_operations, pushing_pushing_an_empty_stack_does_not_update_history, .disabled=0)
{
	t_list *a = NULL;
	t_list *b = NULL;
	t_list	*history = NULL;

	push_first_element_of_a_to_b(&a, &b, &history);

	cr_assert_null(history);
	ft_lstclear(&a, free);
	ft_lstclear(&b, free);
	ft_lstclear(&history, do_not_free_content);
}

Test(test_stack_operations, pushing_element_to_b_updates_field_in_element, .disabled=0)
{
	t_list *a = generate_stack_a(1);
	t_list *b = NULL;

	push_first_element_of_a_to_b(&a, &b, NULL);

	cr_assert_eq(CONTENT_OF_ELEMENT(b)->is_on_stack_a, 0);
	ft_lstclear(&a, free);
	ft_lstclear(&b, free);
}

Test(test_stack_operations, pushing_from_a_removes_element_from_a, .disabled=0)
{
	t_list *a = generate_stack_a(1);
	t_list *b = NULL;

	push_first_element_of_a_to_b(&a, &b, NULL);

	cr_assert_null(a);
	ft_lstclear(&a, free);
	ft_lstclear(&b, free);
}

Test(test_stack_operations, pushing_twice)
{
	t_list *a = generate_stack_a(2);
	t_list *stack = NULL;
	push_first_element_of_a_to_b(&a, &stack, 0);
	push_first_element_of_a_to_b(&a, &stack, 0);

	cr_assert_null(a);
	cr_assert_not_null(stack->next);
	ft_lstclear(&stack, free);
}

Test(test_stack_operations, swapping_empty_stack_does_noting, .disabled=0)
{
	t_list *a = NULL;

	swap_first_two_elements(&a, 0);
	ft_lstclear(&a, free);
}

Test(test_stack_operations, swapping_stack_with_one_element_does_noting, .disabled=0)
{
	t_list 	*stack = generate_stack_a(1);
	t_list	*history = NULL;

	swap_first_two_elements(&stack, &history);

	cr_assert_eq(CONTENT_OF_ELEMENT(stack)->index, 0);
	cr_assert_null(history);
	ft_lstclear(&stack, free);
	ft_lstclear(&history, do_not_free_content);
}

Test(test_stack_operations, swapping_stack_changes_positions_of_first_and_second_element, .disabled=0)
{
	t_list *stack = generate_stack_a(2);

	swap_first_two_elements(&stack, 0);

	cr_assert_eq(CONTENT_OF_ELEMENT(stack)->index, 1);
	ft_lstclear(&stack, free);
}

Test(test_stack_operations, swapping_stack_a_writes_sa_to_history, .disabled=0)
{
	t_list *a = generate_stack_a(2);
	t_list	*history = NULL;

	swap_first_two_elements(&a, &history);

	cr_assert_str_eq(history->content, "sa\n");
	ft_lstclear(&a, free);
	ft_lstclear(&history, do_not_free_content);
}

Test(test_stack_operations, swapping_stack_b_writes_sb_to_history, .disabled=0)
{
	t_list *b = generate_stack_b(2);

	t_list	*history = NULL;

	swap_first_two_elements(&b, &history);

	cr_assert_str_eq(history->content, "sb\n");
	ft_lstclear(&b, free);
	ft_lstclear(&history, do_not_free_content);
}

Test(test_stack_operations, swapping_stack_does_not_affect_other_elements, .disabled=0)
{
	t_list *stack = generate_stack_a(3);

	swap_first_two_elements(&stack, 0);

	cr_assert_eq(CONTENT_OF_ELEMENT(ft_lstget_element_by_index(stack, 2))->index, 2);
	ft_lstclear(&stack, free);
}

Test(test_stack_operations, rotating_empty_stack_does_nothing, .disabled=0)
{
	t_list *stack = NULL;

	rotate(&stack, NULL);
}


Test(test_stack_operations, rotating_stack_with_one_element_does_nothing, .disabled=0)
{
	t_list *stack = generate_stack_a(1);
	t_list *history = NULL;

	rotate(&stack, &history);

	cr_assert_eq(CONTENT_OF_ELEMENT(stack)->index, 0);
	cr_assert_null(history);
	ft_lstclear(&stack, free);
	ft_lstclear(&history, do_not_free_content);
}

Test(test_stack_operations, rotating_stack_with_two_element_swaps, .disabled=0)
{
	t_list *stack = generate_stack_a(2);

	rotate(&stack, NULL);

	cr_assert_eq(CONTENT_OF_ELEMENT(stack)->index, 1);
	cr_assert_null(stack->prev);
	cr_assert_eq(stack->next->prev, stack);
	ft_lstclear(&stack, free);
}

Test(test_stack_operations, rotating_stack_a_writes_ra_to_history, .disabled=0)
{
	t_list *a = generate_stack_a(2);
	t_list *history = NULL;

	rotate(&a, &history);

	cr_assert_str_eq(history->content, "ra\n");
	ft_lstclear(&a, free);
	ft_lstclear(&history, do_not_free_content);
}

Test(test_stack_operations, rotating_stack_b_writes_rb_to_history, .disabled=0)
{
	t_list *b = generate_stack_b(2);
	t_list *history = NULL;

	rotate(&b, &history);

	cr_assert_str_eq(history->content, "rb\n");
	ft_lstclear(&b, free);
	ft_lstclear(&history, do_not_free_content);
}

Test(test_stack_operations, rotating_three_elements_makes_last_first_and_first_second, .disabled=0)
{
	t_list *stack = generate_stack_a(3);

	rotate(&stack, NULL);

	cr_assert_eq(CONTENT_OF_ELEMENT(ft_lstget_element_by_index(stack, 0))->index, 2);
	cr_assert_eq(CONTENT_OF_ELEMENT(ft_lstget_element_by_index(stack, 1))->index, 0);
	cr_assert_eq(CONTENT_OF_ELEMENT(ft_lstget_element_by_index(stack, 2))->index, 1);
	cr_assert_null(ft_lstget_element_by_index(stack, 2)->next);
	ft_lstclear(&stack, free);
}

Test(test_stack_operations, reverse_rotating_stack_with_one_element_does_nothing, .disabled=0)
{
	t_list *stack = generate_stack_a(1);
	t_list *history = NULL;

	reverse_rotate(&stack, &history);

	cr_assert_eq(CONTENT_OF_ELEMENT(stack)->index, 0);
	cr_assert_null(history);
	ft_lstclear(&stack, free);
	ft_lstclear(&history, do_not_free_content);
}

Test(test_stack_operations, reverse_rotating_stack_with_two_element_swaps, .disabled=0)
{
	t_list *stack = generate_stack_a(2);

	reverse_rotate(&stack, NULL);

	cr_assert_eq(CONTENT_OF_ELEMENT(stack)->index, 1);
	cr_assert_null(stack->prev);
	cr_assert_eq(stack->next->prev, stack);
	ft_lstclear(&stack, free);
}

Test(test_stack_operations, reverse_rotating_stack_a_writes_rra_to_history, .disabled=0)
{
	t_list *stack = generate_stack_a(2);
	t_list *history = NULL;

	reverse_rotate(&stack, &history);

	cr_assert_str_eq(history->content, "rra\n");
	ft_lstclear(&stack, free);
	ft_lstclear(&stack, do_not_free_content);
	ft_lstclear(&history, do_not_free_content);
}

Test(test_stack_operations, reverse_rotating_stack_b_writes_rrb_to_history, .disabled=0)
{
	t_list *stack = generate_stack_b(2);
	t_list *history = NULL;

	reverse_rotate(&stack, &history);

	cr_assert_str_eq(history->content, "rrb\n");
	ft_lstclear(&stack, free);
	ft_lstclear(&history, do_not_free_content);
}

Test(test_stack_operations, reverse_rotating_three_elements_makes_last_first_and_first_second, .disabled=0)
{
	t_list *stack = generate_stack_a(3);

	reverse_rotate(&stack, NULL);

	cr_assert_eq(CONTENT_OF_ELEMENT(ft_lstget_element_by_index(stack, 0))->index, 1);
	cr_assert_eq(CONTENT_OF_ELEMENT(ft_lstget_element_by_index(stack, 1))->index, 2);
	cr_assert_eq(CONTENT_OF_ELEMENT(ft_lstget_element_by_index(stack, 2))->index, 0);
	cr_assert_null(ft_lstget_element_by_index(stack, 2)->next);
	ft_lstclear(&stack, free);
}

Test(test_stack_operations, closing_ring_makes_connection_from_last_element_to_first, .disabled=0)
{
	t_list *stack = generate_stack_a(2);
	t_list	*last_element = ft_lstlast(stack);

	close_stack_ring(stack, last_element);

	cr_assert_eq(ft_lstget_element_by_index(stack, 1)->next, stack);
	cr_assert_eq(stack->prev, ft_lstget_element_by_index(stack, 1));
	open_stack_ring(stack, last_element);
	ft_lstclear(&stack, free);
}

Test(test_stack_operations, opening_ring_sets_first_prev_and_last_next_to_NULL, .disabled=0)
{
	t_list *stack = generate_stack_a(2);
	t_list	*last_element = ft_lstlast(stack);

	close_stack_ring(stack, last_element);
	open_stack_ring(stack, last_element);

	cr_assert_null(ft_lstget_element_by_index(stack, 1)->next);
	cr_assert_null(stack->prev);
	ft_lstclear(&stack, free);
}