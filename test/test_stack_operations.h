#include "test_utils.h"


Test(test_stack_operations, pushing_from_empty_stack_does_noting)
{
	t_meta_stack	*a = new_meta_stack();
	t_meta_stack	*b = new_meta_stack();

	push_first_element_to_the_other_stack(a, b, NULL);
}

Test(test_stack_operations, pushing_from_a_puts_element_in_front_of_b)
{
	t_meta_stack	*a = generate_stack_a(1);
	t_meta_stack	*b = generate_stack_b(0);

	push_first_element_to_the_other_stack(a, b, NULL);

	cr_assert_eq(get_content_of_element(b->stack)->index, 0);
	ft_lstclear(&a->stack, free);
	ft_lstclear(&b->stack, free);
	free(a);
	free(b);
}

Test(test_stack_operations, pushing_updates_history_list)
{
	t_meta_stack	*a = generate_stack_a(1);
	t_meta_stack	*b = generate_stack_b(0);
	t_list			*history = NULL;

	push_first_element_to_the_other_stack(a, b, &history);

	cr_assert_str_eq(history->content, "pb\n");
	ft_lstclear(&a->stack, free);
	ft_lstclear(&b->stack, free);
	free(a);
	free(b);
	ft_lstclear(&history, do_not_free_content);
}

Test(test_stack_operations, pushing_updates_prev_for_following_element)
{
	t_meta_stack	*a = generate_stack_a(2);
	t_meta_stack	*b = generate_stack_b(0);
	push_first_element_to_the_other_stack(a, b, NULL);

	cr_assert_null(a->stack->prev);
	ft_lstclear(&a->stack, free);
	ft_lstclear(&b->stack, free);
	free(a);
	free(b);
}

Test(test_stack_operations, pushing_updates_size_in_both_stacks)
{
	t_meta_stack	*a = generate_stack_a(1);
	t_meta_stack	*b = generate_stack_b(0);
	push_first_element_to_the_other_stack(a, b, NULL);

	cr_assert_eq(b->size, 1);
	cr_assert_eq(a->size, 0);
	ft_lstclear(&a->stack, free);
	ft_lstclear(&b->stack, free);
	free(a);
	free(b);
}

Test(test_stack_operations, pushing_on_empty_list_updates_meta_last)
{
	t_meta_stack	*a = generate_stack_a(1);
	t_meta_stack	*b = generate_stack_b(0);

	push_first_element_to_the_other_stack(a, b, NULL);

	cr_assert_eq(b->last, b->stack);
	ft_lstclear(&a->stack, free);
	ft_lstclear(&b->stack, free);
	free(a);
	free(b);
}

Test(test_stack_operations, pushing_from_b_writes_pa_in_history_list)
{
	t_meta_stack	*a = generate_stack_a(0);
	t_meta_stack	*b = generate_stack_b(1);
	t_list			*history = NULL;

	push_first_element_to_the_other_stack(b, a, &history);

	cr_assert_str_eq(history->content, "pa\n");
	ft_lstclear(&a->stack, free);
	ft_lstclear(&b->stack, free);
	free(a);
	free(b);
	ft_lstclear(&history, do_not_free_content);
}

Test(test_stack_operations, pushing_pushing_an_empty_stack_does_not_update_history)
{
	t_meta_stack	*a = generate_stack_a(0);
	t_meta_stack	*b = generate_stack_b(0);
	t_list			*history = NULL;

	push_first_element_to_the_other_stack(a, b, &history);

	cr_assert_null(history);
	ft_lstclear(&a->stack, free);
	ft_lstclear(&b->stack, free);
	free(a);
	free(b);
	ft_lstclear(&history, do_not_free_content);
}

Test(test_stack_operations, pushing_from_a_removes_element_from_a)
{
	t_meta_stack	*a = generate_stack_a(1);
	t_meta_stack	*b = generate_stack_b(0);

	push_first_element_to_the_other_stack(a, b, NULL);

	cr_assert_null(a->stack);
	ft_lstclear(&a->stack, free);
	ft_lstclear(&b->stack, free);
	free(a);
	free(b);
}

Test(test_stack_operations, pushing_twice)
{
	t_meta_stack	*a = generate_stack_a(2);
	t_meta_stack	*b = generate_stack_b(0);

	push_first_element_to_the_other_stack(a, b, 0);
	push_first_element_to_the_other_stack(a, b, 0);

	cr_assert_null(a->stack);
	cr_assert_not_null(b->stack->next);
	ft_lstclear(&a->stack, free);
	ft_lstclear(&b->stack, free);
	free(a);
	free(b);
}

// TODO: pushing_deminishes_size_on_a_and_increases_on_b

Test(test_stack_operations, swapping_empty_stack_does_noting)
{
	t_meta_stack	*a = generate_stack_a(0);

	swap_first_two_elements(a, 0);
	ft_lstclear(&a->stack, free);
	free(a);
}

Test(test_stack_operations, swapping_updates_prev_and_next)
{
	t_meta_stack	*a = generate_stack_a(3);
	t_list			*first_element = a->stack;
	t_list			*second_element = first_element->next;
	t_list			*third_element = second_element->next;

	swap_first_two_elements(a, NULL);
	cr_assert_null(second_element->prev);
	cr_assert_eq(first_element->prev, second_element);
	cr_assert_eq(first_element->next, third_element);
	cr_assert_eq(second_element->next, first_element);
	cr_assert_eq(third_element->prev, first_element);
	ft_lstclear(&a->stack, free);
	free(a);
}

Test(test_stack_operations, if_swapping_two_element_list_set_head_accordingly)
{
	t_meta_stack	*a = generate_stack_a(2);
	t_list			*first_element = a->stack;
	t_list			*second_element = first_element->next;

	swap_first_two_elements(a, NULL);
	cr_assert_eq(a->last, first_element);
	cr_assert_eq(a->stack, second_element);
	ft_lstclear(&a->stack, free);
	free(a);
}

Test(test_stack_operations, swapping_updates_meta_data)
{
	t_meta_stack	*a = generate_stack_a(2);
	t_list			*second_element = a->stack->next;

	swap_first_two_elements(a, 0);

	cr_assert_eq(second_element, a->stack);
	ft_lstclear(&a->stack, free);
	free(a);
}

Test(test_stack_operations, swapping_stack_with_one_element_does_noting)
{
	t_meta_stack 	*a = generate_stack_a(1);
	t_list	*history = NULL;

	swap_first_two_elements(a, &history);

	cr_assert_eq(get_content_of_element(a->stack)->index, 0);
	cr_assert_null(history);
	ft_lstclear(&a->stack, free);
	free(a);
	ft_lstclear(&history, do_not_free_content);
}

Test(test_stack_operations, swapping_stack_changes_positions_of_first_and_second_element)
{
	t_meta_stack 	*a = generate_stack_a(2);

	swap_first_two_elements(a, 0);

	cr_assert_eq(get_content_of_element(a->stack)->index, 1);
	ft_lstclear(&a->stack, free);
	free(a);
}

Test(test_stack_operations, swapping_stack_a_writes_sa_to_history)
{
	t_meta_stack 	*a = generate_stack_a(2);

	t_list	*history = NULL;

	swap_first_two_elements(a, &history);

	cr_assert_str_eq(history->content, "sa\n");
	ft_lstclear(&a->stack, free);
	free(a);
	ft_lstclear(&history, do_not_free_content);
}

Test(test_stack_operations, swapping_stack_b_writes_sb_to_history)
{
	t_meta_stack 	*b = generate_stack_b(2);
	t_list	*history = NULL;

	swap_first_two_elements(b, &history);

	cr_assert_not_null(history);
	cr_assert_str_eq(history->content, "sb\n");
	ft_lstclear(&b->stack, free);
	free(b);
	ft_lstclear(&history, do_not_free_content);
}

Test(test_stack_operations, swapping_stack_does_not_affect_other_elements)
{
	t_meta_stack 	*a = generate_stack_a(3);

	swap_first_two_elements(a, 0);

	cr_assert_eq(get_content_of_element(ft_lstget_element_by_index(a->stack, 2))->index, 2);
	ft_lstclear(&a->stack, free);
	free(a);
}

Test(test_stack_operations, rotating_empty_stack_does_nothing)
{
	t_meta_stack	*stack = new_meta_stack();

	reverse_rotate(stack, NULL);
}


Test(test_stack_operations, rotating_stack_with_one_element_does_nothing)
{
	t_meta_stack 	*a = generate_stack_a(1);
	t_list *history = NULL;

	reverse_rotate(a, &history);

	cr_assert_eq(get_content_of_element(a->stack)->index, 0);
	cr_assert_null(history);
	ft_lstclear(&a->stack, free);
	free(a);
	ft_lstclear(&history, do_not_free_content);
}

Test(test_stack_operations, rotating_stack_with_two_element_swaps)
{
	t_meta_stack 	*a = generate_stack_a(2);

	reverse_rotate(a, NULL);

	cr_assert_eq(get_content_of_element(a->stack)->index, 1);
	cr_assert_null(a->stack->prev);
	cr_assert_eq(a->stack->next->prev, a->stack);
	ft_lstclear(&a->stack, free);
	free(a);
}

Test(test_stack_operations, rotate_updates_meta_data)
{
	t_meta_stack 	*a = generate_stack_a(3);
	t_list			*second_element = a->stack->next;
	t_list			*third_element = a->stack->next->next;

	reverse_rotate(a, NULL);

	cr_assert_eq(a->stack, third_element);
	cr_assert_eq(a->last, second_element);
	ft_lstclear(&a->stack, free);
	free(a);
}
Test(test_stack_operations, rotating_stack_a_writes_ra_to_history)
{
	t_meta_stack 	*a = generate_stack_a(2);
	t_list *history = NULL;

	reverse_rotate(a, &history);

	cr_assert_str_eq(history->content, "ra\n");
	ft_lstclear(&a->stack, free);
	free(a);
	ft_lstclear(&history, do_not_free_content);
}

Test(test_stack_operations, rotating_stack_b_writes_rb_to_history)
{
	t_meta_stack 	*b = generate_stack_b(2);
	t_list *history = NULL;

	reverse_rotate(b, &history);

	cr_assert_str_eq(history->content, "rb\n");
	ft_lstclear(&b->stack, free);
	free(b);
	ft_lstclear(&history, do_not_free_content);
}

Test(test_stack_operations, rotating_three_elements_makes_last_first_and_first_second)
{
	t_meta_stack 	*a = generate_stack_a(3);

	reverse_rotate(a, NULL);

	cr_assert_eq(get_content_of_element(ft_lstget_element_by_index(a->stack, 0))->index, 2);
	cr_assert_eq(get_content_of_element(ft_lstget_element_by_index(a->stack, 1))->index, 0);
	cr_assert_eq(get_content_of_element(ft_lstget_element_by_index(a->stack, 2))->index, 1);
	cr_assert_null(ft_lstget_element_by_index(a->stack, 2)->next);
	cr_assert_null(a->stack->prev);
	ft_lstclear(&a->stack, free);
	free(a);
}

Test(test_stack_operations, reverse_rotating_stack_with_one_element_does_nothing)
{
	t_meta_stack	*a = generate_stack_a(1);
	t_list 			*history = NULL;

	rotate(a, &history);

	cr_assert_eq(get_content_of_element(a->stack)->index, 0);
	cr_assert_null(history);
	ft_lstclear(&a->stack, free);
	free(a);
	ft_lstclear(&history, do_not_free_content);
}

Test(test_stack_operations, reverse_rotating_stack_with_two_element_swaps)
{
	t_meta_stack	*a = generate_stack_a(2);

	rotate(a, NULL);

	cr_assert_eq(get_content_of_element(a->stack)->index, 1);
	cr_assert_null(a->stack->prev);
	cr_assert_eq(a->stack->next->prev, a->stack);
	ft_lstclear(&a->stack, free);
	free(a);
}

Test(test_stack_operations, reverse_rotating_stack_a_writes_rra_to_history)
{
	t_meta_stack	*a = generate_stack_a(2);
	t_list			*history = NULL;

	rotate(a, &history);

	cr_assert_str_eq(history->content, "rra\n");
	ft_lstclear(&a->stack, free);
	free(a);
	ft_lstclear(&history, do_not_free_content);
}

Test(test_stack_operations, reverse_rotating_write_meta_data)
{
	t_meta_stack	*a = generate_stack_a(3);
	t_list			*first_element = a->stack;

	rotate(a, NULL);

	cr_assert_eq(a->last, first_element);
	ft_lstclear(&a->stack, free);
	free(a);
}

Test(test_stack_operations, reverse_rotating_stack_b_writes_rrb_to_history)
{
	t_meta_stack	*a = generate_stack_b(2);
	t_list			*history = NULL;

	rotate(a, &history);

	cr_assert_str_eq(history->content, "rrb\n");
	ft_lstclear(&a->stack, free);
	free(a);
	ft_lstclear(&history, do_not_free_content);
}

Test(test_stack_operations, reverse_rotating_three_elements_makes_last_first_and_first_second)
{
	t_meta_stack	*a = generate_stack_a(3);

	rotate(a, NULL);

	cr_assert_eq(get_content_of_element(ft_lstget_element_by_index(a->stack, 0))->index, 1);
	cr_assert_eq(get_content_of_element(ft_lstget_element_by_index(a->stack, 1))->index, 2);
	cr_assert_eq(get_content_of_element(ft_lstget_element_by_index(a->stack, 2))->index, 0);
	cr_assert_null(ft_lstget_element_by_index(a->stack, 2)->next);
	ft_lstclear(&a->stack, free);
	free(a);
}

Test(test_stack_operations, closing_ring_makes_connection_from_last_element_to_first)
{
	t_meta_stack	*a = generate_huge_stack();
	t_list			*first_element = a->stack;
	t_list			*last_element = ft_lstlast(a->stack);

	close_stack_ring(a->stack, last_element);

	cr_assert_eq(last_element->next, first_element);
	cr_assert_eq(a->stack->prev, last_element);
	open_stack_ring(a->stack, last_element);
	ft_lstclear(&a->stack, free);
	free(a);
}

Test(test_stack_operations, opening_ring_sets_first_prev_and_last_next_to_NULL)
{
	t_meta_stack	*a = generate_huge_stack(2);
	t_list			*last_element = a->last;

	close_stack_ring(a->stack, last_element);
	open_stack_ring(a->stack, last_element);

	cr_assert_null(a->last->next);
	cr_assert_null(a->stack->prev);
	ft_lstclear(&a->stack, free);
	free(a);
}
