#include "test_utils.h"

const char	**create_valid_input(int len)
{
	const char	**result = malloc(sizeof (char *) * (len + 1));
	result[len] = NULL;
	while (len-- > 0)
		result[len] = ft_itoa(len);
	return (result);
}

const char	**create_invalid_input(int len)
{
	const char	**result = malloc(sizeof (char *) * (len + 1));
	result[len] = NULL;
	while (len-- > 0)
		result[len] = ft_itoa(0);
	return (result);
}

Test(test_parsing, input_contains_not_parsable)
{
	cr_assert(! is_str_parsable("p "));
	cr_assert(! is_str_parsable("agorgh"));
	cr_assert(! is_str_parsable("234923525f"));
	cr_assert(! is_str_parsable(" p"));
	cr_assert(! is_str_parsable(""));
	cr_assert(! is_str_parsable("-"));
	cr_assert(! is_str_parsable("+"));
	cr_assert(! is_str_parsable("1342-"));
	cr_assert(! is_str_parsable("-p"));
}

Test(test_parsing, input_is_parsable)
{
	cr_assert(is_str_parsable("2147483647"));
	cr_assert(is_str_parsable("12"));
	cr_assert(is_str_parsable("-2147483648"));
}

Test(test_parsing, input_does_fit_into_int)
{
	cr_assert(does_fit_into_int("2147483647"));
	cr_assert(does_fit_into_int("  37239"));
	cr_assert(does_fit_into_int("-2147483648"));
	cr_assert(does_fit_into_int("0"));
	cr_assert(does_fit_into_int("19"));
	cr_assert(does_fit_into_int("09"));
}

Test(test_parsing, input_does_not_fit_into_int)
{
	char	*in = "2147483648";

	int		is_parsable = does_fit_into_int(in);

	cr_assert(! is_parsable);
}

Test(test_parsing, duplicate_entry)
{
	char	*in[4];
	in[0] = "0";
	in[1] = "1";
	in[2] = "0";
	in[3] = 0;

	int res_act = does_contain_duplication(4, (const char **) in);

	cr_assert(res_act);
}


Test(test_parsing, parse_int_min_succeeds)
{
	char		*in = "-2147483648";

	t_content	*res = parse_one_string(in);

	cr_assert_eq(res->i, INT_MIN);
	free(res);
}

Test(test_parsing, single_str_can_be_handled_by_atoi)
{
	int				argc = 1;
	const char		**argv = create_valid_input(argc);

	t_meta_stack	*int_input = generate_stack(argc, argv);

	cr_assert_eq(CONTENT_OF_ELEMENT(int_input->stack)->i, 0);
	free_2d_char_array((char**) argv);
	ft_lstclear(&int_input->stack, free);
	free(int_input);
}

Test(test_parsing, input_is_simple_valid_string_array)
{
	int		argc = 2;
	const char	**argv = create_valid_input(argc);

	t_meta_stack	*int_input = generate_stack(argc + 1, argv);

	cr_assert_not_null(int_input->stack);
	cr_assert_eq(CONTENT_OF_ELEMENT(int_input->stack)->i, 0);
	cr_assert_eq(int_input->size, 2);
	cr_assert_eq(CONTENT_OF_ELEMENT(int_input->stack->next)->i, 1);
	free_2d_char_array((char**) argv);
	ft_lstclear(&int_input->stack, free);
	free(int_input);
}

Test(test_parsing, invalid_duplicate_input)
{
	int		argc = 2;
	const char	**argv = create_invalid_input(argc + 1);

	cr_assert(does_contain_duplication(argc, argv));
	t_meta_stack	*int_input = generate_stack(argc, argv);

	cr_assert_null(int_input);
	free_2d_char_array((char**) argv);
}

Test(test_parsing, created_stack_has_all_prevs)
{
	t_meta_stack	*meta_stack = generate_huge_stack();

	cr_assert(all_prevs_are_properly_set(meta_stack));
	ft_lstclear(&meta_stack->stack, free);
	free(meta_stack);
}

Test(test_parsing, free_whole_list_if_one_not_parsable)
{
	char	*in[3];
	in[0] = "0";
	in[1] = "w";
	in[2] = 0;

	t_meta_stack	*res = generate_stack(2, (const char **) in);

	cr_assert_null(res);
}

