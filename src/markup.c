#include <stdio.h>
#include "push_swap.h"

void markup_stack_by_reference(t_meta_stack *meta_stack,
							   t_list *reference,
							   enum markup_mode mode)
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
		markup_one_element(stack, &global_max_value, mode);
		stack = stack->next;
		has_reached_start = (stack == reference);
	}
	open_stack_ring(meta_stack->stack, meta_stack->last);
}


void markup_element_in_value_mode(int *global_max, t_content *content)
{
	content->should_stay_on_stack_a = content->i >= *global_max;
	if (content->should_stay_on_stack_a)
		*global_max = content->i;
}

void markup_element_in_index_mode(int *global_max, t_content *content)
{
	content->should_stay_on_stack_a = content->index == *global_max + 1;
	if (content->should_stay_on_stack_a)
		(*global_max)++;
}

void markup_one_element(t_list *element_to_be_marked_up, int *global_max,
						enum markup_mode mode)
{
	t_content	*content;

	content = CONTENT_OF_ELEMENT(element_to_be_marked_up);
	if (mode == value_mode)
		markup_element_in_value_mode(global_max, content);
	else
		markup_element_in_index_mode(global_max, content);
}
