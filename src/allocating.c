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

t_meta_stack * new_meta_stack(void)
{
	t_meta_stack	*result;

	result = malloc(sizeof (t_meta_stack));
	result->stack = NULL;
	result->size = 0;
	result->last = 0;
	result->is_stack_a = 1;
	return (result);
}

int	*malloc_int(int in)
{
	int	*result;

	result = malloc (sizeof(int));
	if (! result)
		return (NULL);
	*result = in;
	return (result);
}