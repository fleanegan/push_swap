#include "test_utils.h"

Test(test_list_index, indexing_an_empty_stack_does_nothing)
{
	t_list	*stack = NULL;

	index_stack(stack);
}

Test(test_list_index, new_item_appears_on_stack_a)
{
	t_content *content = new_stack_content(0);

	cr_assert(content->is_on_stack_a);
	free(content);
}

Test(test_list_index, indexing_a_stack_does_not_change_its_order)
{
	t_list	*stack = ft_lstnew(new_stack_content(1));
	t_list	*b = ft_lstnew(new_stack_content(0));
	ft_lstadd_back(&stack, b);

	index_stack(stack);

	cr_assert_eq(stack->next, b);
	ft_lstclear(&stack, free);
}

Test(test_list_index, indexing_a_stack_writes_the_index_into_the_content_struct)
{
	t_list	*stack = ft_lstnew(new_stack_content(1));
	t_list	*b = ft_lstnew(new_stack_content(0));
	ft_lstadd_back(&stack, b);

	index_stack(stack);

	cr_assert_eq(((t_content *)(stack->content))->index, 1);
	cr_assert_eq(((t_content *)(stack->next->content))->index, 0);
	ft_lstclear(&stack, free);
}
