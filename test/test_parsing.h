#include "test_utils.h"

const char	**create_valid_input(int len)
{
	const char	**result = malloc(sizeof (char *) * (len + 1));
	result[len] = NULL;
	while (len-- > 0)
		result[len] = ft_itoa(len);
	return (result);
}

Test(test_parsing, single_str_can_be_handled_by_atoi)
{
	int		argc = 1;
	const char	**argv = create_valid_input(argc);

	t_list	*int_input = char_input_to_int_list(argc, argv);

	cr_assert_eq(*(int*) int_input->content, 0, "act val %d", *(int*) int_input->content);
	free_2d_char_array((char**) argv);
	ft_lstclear(&int_input, free);
}

Test(test_parsing, input_is_simple_valid_string_array)
{
	int		argc = 2;
	const char	**argv = create_valid_input(argc);

	t_list	*int_input = char_input_to_int_list(argc, argv);

	cr_assert_eq(*(int*) int_input->content, 0, "act val %d", *(int*) int_input->content);
	cr_assert_eq(*(int*) int_input->next->content, 1, "act val %d", *(int*) int_input->next->content);
	free_2d_char_array((char**) argv);
	ft_lstclear(&int_input, free);
}

Test(test_parsing, input_contains_not_parsable)
{
	cr_assert(! is_str_parsable("p"));
	cr_assert(! is_str_parsable("agorgh"));
	cr_assert(! is_str_parsable("  		234923525f"));
	cr_assert(! is_str_parsable("p"));
	cr_assert(! is_str_parsable("p"));
	cr_assert(! is_str_parsable("p"));
	cr_assert(! is_str_parsable("p"));
}

Test(test_parsing, input_is_parsable)
{
	cr_assert(is_str_parsable("    2147483647"));
	cr_assert(is_str_parsable("				12"));
	cr_assert(is_str_parsable("  	  "));
	cr_assert(is_str_parsable("-"));
	cr_assert(is_str_parsable("+"));
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
	char	*in[3];
	in[0] = "0";
	in[1] = "0";
	in[2] = 0;

	int does_contain_duplication = does_contain_duplication(2, (const char **) in);

	cr_assert_null(res);
	//free(res);
}


Test(test_parsing, parse_int_min_with_space)
{
	char	*in = "		 		-2147483648";

	int		*res = parse_one_string(in);

	cr_assert_eq(*res, INT_MIN);
	free(res);
}

Test(test_parsing, free_whole_list_if_one_not_parsable)
{
	char	*in[3];
	in[0] = "0";
	in[1] = "w";
	in[2] = 0;

	t_list	*res = char_input_to_int_list(2, (const char **) in);

	cr_assert_null(res);
	//free(res);
}

//TODO test for duplicate entries