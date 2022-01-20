#include "push_swap.h"

int is_swapping_a_good_idea(t_meta_stack *meta_stack, \
t_list *markup_reference, enum markup_mode mode)
{
	int	markup_count_before;
	int	markup_count_after;

	if (meta_stack->stack && meta_stack->stack->next
		&& (CONTENT_OF_ELEMENT(meta_stack->stack)->should_stay_on_stack_a
			&& CONTENT_OF_ELEMENT(meta_stack->stack->next)->should_stay_on_stack_a))
		return (0);
	markup_count_before = count_markups(meta_stack->stack);
	swap_first_two_elements(meta_stack, NULL);
	markup_stack_by_reference(meta_stack, markup_reference, mode);
	markup_count_after = count_markups(meta_stack->stack);
	swap_first_two_elements(meta_stack, NULL);
	markup_stack_by_reference(meta_stack, markup_reference, mode);
	if (markup_count_before < markup_count_after)
		return (1);
	return (0);
}

int	count_elements_to_be_moved_to_b(t_meta_stack *a)
{
	return ((int) (a->size - count_markups(a->stack)));
}

int	count_markups(const t_list *stack)
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
