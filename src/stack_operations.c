#include <stdio.h>
#include "push_swap.h"

void	update_history(t_list **history, const void *caller_identifier, const int is_on_stack_a);
void	cut_element_from_a_to_b(t_meta_stack *a, t_meta_stack *b);
t_list	*pop_first_element_from_list(t_list **stack);
t_list	*detach_last_element_from_list(t_list *stack);

void	push_first_element_of_a_to_b(t_meta_stack *a, t_meta_stack *b, t_list **history)
{
	if (a && a->stack)
	{
		cut_element_from_a_to_b(a, b);
		a->size--;
		if (! b->size++)
			b->last = b->stack;
		update_history(history, push_first_element_of_a_to_b, a->is_stack_a);
	}
}

void	cut_element_from_a_to_b(t_meta_stack *a, t_meta_stack *b) {
	t_list		*tmp;

	tmp = a->stack->next;
	ft_lstadd_front(&b->stack, a->stack);
	a->stack = tmp;
	if (tmp)
		tmp->prev = NULL;
}

void	swap_first_two_elements(t_meta_stack *meta_stack, t_list **history)
{
	t_list	*tmp;

	if (meta_stack && meta_stack->stack && meta_stack->stack->next)
	{
		tmp = meta_stack->stack->next;
		meta_stack->stack->next = tmp->next;
		tmp->next = meta_stack->stack;
		meta_stack->stack = tmp;
		update_history(history, swap_first_two_elements, meta_stack->is_stack_a);
	}
}

void	rotate(t_meta_stack *meta_stack, t_list **history)
{
	t_list	*last_element;

	if (meta_stack->stack && meta_stack->stack->next)
	{
		last_element = detach_last_element_from_list(meta_stack->stack);
		meta_stack->last = last_element->prev;
		ft_lstadd_front(&meta_stack->stack, last_element);
		update_history(history, rotate, meta_stack->is_stack_a);
	}
}

t_list	*detach_last_element_from_list(t_list *stack) {
	t_list	*result;

	while (stack->next && stack->next->next)
		stack = stack->next;
	result = stack->next;
	stack->next = NULL;
	return (result);
}

void	reverse_rotate(t_meta_stack *meta_stack, t_list **history)
{
	t_list	*first_element;

	if (meta_stack->stack && meta_stack->stack->next)
	{
		first_element = pop_first_element_from_list(&meta_stack->stack);
		meta_stack->last = first_element;
		ft_lstadd_back(&meta_stack->stack, first_element);
		update_history(history, reverse_rotate, meta_stack->is_stack_a);
	}
}

t_list	*pop_first_element_from_list(t_list **stack)
{
	t_list *tmp;

	tmp = *stack;
	*stack = (*stack)->next;
	tmp->next = NULL;
	(*stack)->prev = NULL;
	return (tmp);
}

void	update_history(t_list **history, const void *caller_identifier, const int is_on_stack_a)
{
	if (history)
	{
		if (caller_identifier == rotate)
		{
			if (is_on_stack_a)
				ft_lstadd_back(history, ft_lstnew("ra\n"));
			else
				ft_lstadd_back(history, ft_lstnew("rb\n"));
		}
		if (caller_identifier == reverse_rotate)
		{
			if (is_on_stack_a)
				ft_lstadd_back(history, ft_lstnew("rra\n"));
			else
				ft_lstadd_back(history, ft_lstnew("rrb\n"));
		}
		if (caller_identifier == swap_first_two_elements)
		{
			if (is_on_stack_a)
				ft_lstadd_back(history, ft_lstnew("sa\n"));
			else
				ft_lstadd_back(history, ft_lstnew("sb\n"));
		}
		else if (caller_identifier == push_first_element_of_a_to_b)
		{
			if (is_on_stack_a)
				ft_lstadd_back(history, ft_lstnew("pb\n"));
			else
				ft_lstadd_back(history, ft_lstnew("pa\n"));
		}
	}
}

void	close_stack_ring(t_list *stack, t_list *last_element)
{
	if (stack)
		stack->prev = last_element;
	if (last_element)
		last_element->next = stack;
}

void	open_stack_ring(t_list *stack, t_list *last_element)
{
	if (stack)
		stack->prev = NULL;
	if (last_element)
		last_element->next = NULL;
}

