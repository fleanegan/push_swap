#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# define CONTENT_OF_ELEMENT(x) (((t_content *)((x)->content)))
# include "libft_auxilliar.h"
# include <limits.h>

typedef struct s_content
{
	int	i;
	int	index;
	int	is_on_stack_a;
	int	should_stay_on_stack_a;
}	t_content;

typedef struct s_meta_stack
{
	size_t	size;
	int		is_stack_a;
	t_list	*stack;
	t_list	*last;
}	t_meta_stack;

t_meta_stack	*new_meta_stack(void);
void			push_first_element_to_the_other_stack(t_meta_stack *a, t_meta_stack *b, t_list **history);
void		swap_first_two_elements(t_meta_stack *meta_stack, t_list **history);
void		rotate(t_meta_stack *meta_stack, t_list **history);
void		reverse_rotate(t_meta_stack *metastack, t_list **history);
void		index_stack(t_list *stack);
t_content	*new_stack_content(int in);
void rotate_stack_n_steps(t_meta_stack *meta_stack, int steps, t_list **history);
void		move_to_top(t_meta_stack *meta_stack, t_list *element_to_move, t_list **history);
void		do_not_free_content(void *content);
void		markup_one_element(t_list *reference, t_list *element_to_be_marked_up, int *global_max);
t_list		*calc_markup_reference(t_meta_stack *meta_stack);
void		markup_all_elements_according_to_reference(t_meta_stack *meta_stack, t_list *reference);
int			count_markups(t_list *stack);
int			is_swapping_a_good_idea(t_meta_stack *meta_stack, t_list *markup_reference);
void		close_stack_ring(t_list *stack, t_list *last_element);
void		open_stack_ring(t_list *stack, t_list *last_element);
void		fill_b(t_meta_stack *a, t_meta_stack *b, t_list **history);
int			count_elements_to_be_moved_to_b(t_list *a);
int			calc_moves_to_top(t_meta_stack *meta_stack, t_list *element);
int			calc_moves_to_bottom(t_meta_stack *meta_stack, t_list *element);
int			calc_moves_to_get_a_in_push_position(t_meta_stack *a, t_list *push_candidate);
void		bring_a_in_push_position(t_meta_stack *a, t_list *push_candidate, t_list **history);
int			sorting_index_equals_to(void *content, int index);
int			calc_moves_to_push_element_onto_a(t_meta_stack *a, t_meta_stack *b, t_list *push_candidate);
t_list		*get_biggest_element_smaller_than_candidate(t_list *a, int value_of_candidate);
t_list		*get_smallest_element_bigger_than_candidate(t_list *a, int value_of_candidate);
t_list		*calc_element_to_push(t_meta_stack *a, t_meta_stack *b);
void		rotate_a_back_in_order(t_meta_stack *a, t_list **history);
void		sort_b_back_into_a(t_meta_stack *a, t_meta_stack *b, t_list **history);
t_list		*russian_algorithm(t_meta_stack *a);
int			*malloc_int(int in);


// parsing
int	is_str_parsable(char *in);
t_content * parse_one_string(char *in);
int	does_fit_into_int(const char *in);
int does_contain_duplication(int argc, const char **argv);
t_meta_stack * generate_stack(int argc, const char **argv);

#endif //PUSH_SWAP_H
