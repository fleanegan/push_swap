#include "test_utils.h"

Test(test_integration, simple_valid_input, .disabled=false)
{
	t_meta_stack	*a = generate_test_stack_0();

	t_list	*history = russian_algorithm(a);

	puts("history for simple valid input");
	cr_assert_not_null(history);
	ft_lstput_str_bonus(history);
	cr_assert_str_eq(history->content, "ra\n");
}