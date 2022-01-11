#include "push_swap.h"

t_content	*new_stack_content(int in)
{
	t_content	*result;

	result = malloc (sizeof(t_content));
	result->i = in;
	result->index = -1;
	result->is_on_stack_a = 1;
	result->should_stay_on_stack_a = 0;
	return (result);
}