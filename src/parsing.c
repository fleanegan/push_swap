#include <stdio.h>
#include "push_swap.h"
#include "libft/libft.h"

int	is_str_parsable(char *in)
{
	while (*in)
	{
		if (! ft_isdigit(*in) && ! ft_isspace(*in)
			&& *in != '+' && *in != '-')
			return (0);
		in++;
	}
	return (1);
}

int	does_fit_into_int(const char *in)
{
	int			sign;
	long int	res;

	sign = 1;
	res = 0;
	while (ft_isspace(*in))
		in++;
	if (*in == '-' || *in == '+')
	{
		if (*in == '-')
			sign = -1;
		in++;
	}
	while (ft_isdigit(*in))
	{
		res = 10 * res + (*in++ - '0');
		if ((res > INT_MAX && sign == 1)
			|| (res > (long) INT_MAX + 1 && sign == -1))
			return (0);
	}
	return (1);
}

int *parse_one_string(char *in)
{
	int	*result;

	if (! is_str_parsable(in) || ! does_fit_into_int(in))
		return (NULL);
	result = malloc_int(ft_atoi(in));
	return (result);
}

t_list	*char_input_to_int_list(int argc, const char **argv)
{
	t_list	*result;
	char 	**tmp;
	int		*tmp_result;

	result = NULL;
	tmp = (char **) argv;
	while (*tmp)
	{
		tmp_result = parse_one_string(*tmp);
		if (! tmp_result)
		{
			ft_lstclear(&result, free);
			return (NULL);
		}
		ft_lstadd_back(&result, ft_lstnew(tmp_result));
		tmp++;
	}
	return (result);
}