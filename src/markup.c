#include <stdio.h>
#include "push_swap.h"

int	is_element_fitter_than_old_candidate(int markup_count, \
int global_max_markup_count, t_list *old_candidate, t_list *new_candidate);

t_list	*calc_markup_reference(t_list *stack) {
	t_list	*first_element;
	t_list	*candidate;
	int		markup_count;
	int		global_max_markup_count;

	candidate = NULL;
	first_element = stack;
	global_max_markup_count = 0;
	while (stack && (! candidate || first_element != stack))
	{
		markup_count = count_markups(stack);
		//printf("dealing with element %d (index %d), which allows %d (current candidate does %d) elements to stay in a \n", CONTENT_OF_ELEMENT(stack)->i, CONTENT_OF_ELEMENT(stack)->index, markup_count,  global_max_markup_count);
		//ft_lstput_nbr_bonus(stack);
		if (! candidate || is_element_fitter_than_old_candidate(markup_count, global_max_markup_count, candidate, stack))
		{
			candidate = stack;
			global_max_markup_count = markup_count;
		}
		//printf("current candidate %d \n", CONTENT_OF_ELEMENT(candidate)->i);
		rotate(&stack, NULL);
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

void	markup_all_elements_according_to_reference(t_list *stack, t_list *candidate)
{
	t_list	*last_element;
	int		has_reached_start;
	int		global_max_value;

	if (! CONTENT_OF_ELEMENT(candidate)->is_on_stack_a)
		return ;
	global_max_value = CONTENT_OF_ELEMENT(candidate)->i;
	has_reached_start = 0;
	last_element = ft_lstlast(stack);
	close_stack_ring(stack, last_element);
	stack = candidate;
	//printf("begin calc with candidate %d\n", CONTENT_OF_ELEMENT(candidate)->i);
	while (! has_reached_start)
	{
		//printf("glob max %d, ce %d \n",global_max_value, CONTENT_OF_ELEMENT(stack)->i);
		markup_one_element(candidate, stack, &global_max_value);
		//printf("candidate %d, curr %d, next %d\n", CONTENT_OF_ELEMENT(candidate)->i, CONTENT_OF_ELEMENT(stack)->i, CONTENT_OF_ELEMENT(stack->next)->i);
		stack = stack->next;
		has_reached_start = (stack == candidate);
	}
	open_stack_ring(stack, last_element);
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

int	is_swapping_a_good_idea(t_list *stack, t_list *markup_reference)
{
	int	markup_count_before;
	int	markup_count_after;

//	puts("is swap");
//	printf("element %d, should stay %d, markup reference %d? \n", CONTENT_OF_ELEMENT(stack)->i, CONTENT_OF_ELEMENT(stack)->should_stay_on_stack_a, CONTENT_OF_ELEMENT(markup_reference)->i);
//	puts("reached first markup for ref");
	markup_all_elements_according_to_reference(stack, markup_reference);
	if (stack->next && (CONTENT_OF_ELEMENT(stack)->should_stay_on_stack_a && CONTENT_OF_ELEMENT(stack->next)->should_stay_on_stack_a))
		return (0);
//	puts("reached first count for ref");
	markup_count_before = count_markups(stack);
//	puts("reached swap");
	swap_first_two_elements(&stack, NULL);
//	puts("reached second markup for ref");
	markup_all_elements_according_to_reference(stack, markup_reference);
//	puts("reached second count for ref");
	markup_count_after = count_markups(stack);
	swap_first_two_elements(&stack, NULL);
//	puts("reached end of swap_checker<--------------");
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