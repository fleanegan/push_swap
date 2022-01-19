#include <stdio.h>
#include "push_swap.h"

int	is_element_fitter_than_old_candidate(int markup_count, \
int global_max_markup_count, t_list *old_candidate, t_list *new_candidate);

t_list	*calc_markup_reference(t_meta_stack *meta_stack)
{
	t_list	*first_element;
	t_list	*candidate;
	int		markup_count;
	int		global_max_markup_count;

	candidate = NULL;
	first_element = meta_stack->stack;
	global_max_markup_count = 0;
	while (meta_stack->stack && (! candidate || first_element != meta_stack->stack))
	{
		markup_count = count_markups(meta_stack->stack);
		if (! candidate ||
			is_element_fitter_than_old_candidate(markup_count, global_max_markup_count, candidate, meta_stack->stack))
		{
			candidate = meta_stack->stack;
			global_max_markup_count = markup_count;
		}
		rotate(meta_stack, NULL);
	}
	return candidate;
}

int	is_element_fitter_than_old_candidate(int markup_count, \
int global_max_markup_count, t_list *old_candidate, t_list *new_candidate)
{
	return (markup_count > global_max_markup_count ||
		(markup_count == global_max_markup_count &&
		CONTENT_OF_ELEMENT(old_candidate)->index > \
		CONTENT_OF_ELEMENT(new_candidate)->index));
}

void	markup_all_elements_according_to_reference(t_meta_stack *meta_stack, t_list *reference)
{
	int		has_reached_start;
	int		global_max_value;
	t_list	*stack;

	stack = meta_stack->stack;
	global_max_value = CONTENT_OF_ELEMENT(reference)->i;
	has_reached_start = 0;
	close_stack_ring(meta_stack->stack, meta_stack->last);
	stack = reference;
	while (! has_reached_start)
	{
		markup_one_element(reference, stack, &global_max_value);
		stack = stack->next;
		has_reached_start = (stack == reference);
	}
	open_stack_ring(meta_stack->stack, meta_stack->last);
}


int	count_markups(t_list *stack)
{
	int		markup_count;

	markup_count = 0;
	while (stack)
	{
		if (CONTENT_OF_ELEMENT(stack)->should_stay_on_stack_a)
			markup_count++;
		stack = stack->next;
	}
	return (markup_count);
}

void	markup_one_element(t_list *reference, t_list *element_to_be_marked_up, int *global_max)
{
	t_content	*content;

	if (reference && element_to_be_marked_up)
	{
		content = CONTENT_OF_ELEMENT(element_to_be_marked_up);
		if (global_max)
		{
			content->should_stay_on_stack_a = content->i >= *global_max;
			if (content->should_stay_on_stack_a)
				*global_max = content->i;
		}
	}
}

int	is_swapping_a_good_idea(t_meta_stack *meta_stack, t_list *markup_reference)
{
	int	markup_count_before;
	int	markup_count_after;

	if (meta_stack->stack && meta_stack->stack->next
		&& (CONTENT_OF_ELEMENT(meta_stack->stack)->should_stay_on_stack_a
		&& CONTENT_OF_ELEMENT(meta_stack->stack->next)->should_stay_on_stack_a))
		return (0);
	markup_count_before = count_markups(meta_stack->stack);
	swap_first_two_elements(meta_stack, NULL);
	markup_all_elements_according_to_reference(meta_stack, markup_reference);
	markup_count_after = count_markups(meta_stack->stack);
	swap_first_two_elements(meta_stack, NULL);
	markup_all_elements_according_to_reference(meta_stack, markup_reference);
	if (markup_count_before < markup_count_after)
		return (1);
	return (0);
}

int	count_elements_to_be_moved_to_b(t_list *a)
{
	int	result;

	result = 0;
	while (a)
	{
		result += ! CONTENT_OF_ELEMENT(a)->should_stay_on_stack_a;
		a = a->next;
	}
	return (result);
}
