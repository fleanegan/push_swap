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

void		push_first_element_of_a_to_b(t_list **a, t_list **b, t_list **history);
void		swap_first_two_elements(t_list **stack, t_list **history);
void		rotate(t_list **stack, t_list **history);
void		reverse_rotate(t_list **stack, t_list **history);
void		index_stack(t_list *stack);
t_content	*new_stack_content(int in);
int			calc_direction_to_top(t_list *stack, t_list *element_to_move);
void		move_to_top(t_list **stack, t_list *element_to_move, t_list **history);
void		do_not_free_content(void *content);
void		markup_one_element(t_list *reference, t_list *element_to_be_marked_up, int *global_max);
t_list		*calc_markup_reference(t_list *stack);
void		markup_all_elements_according_to_reference(t_list *stack, t_list *reference);
int			count_markups(t_list *stack);
int			is_swapping_a_good_idea(t_list *stack, t_list *markup_reference);
void		close_stack_ring(t_list *stack, t_list *last_element);
void		open_stack_ring(t_list *stack, t_list *last_element);
void		fill_b(t_list **a, t_list **b, t_list **history);
int			count_elements_to_be_moved_to_b(t_list *a);
int			calc_moves_to_top(t_list *stack, t_list *element);
int			calc_moves_to_bottom(t_list *stack, t_list *element);
int			calc_moves_to_get_a_in_push_position(t_list *a, t_list *push_candidate);
int			sorting_index_equals_to(void *content, int index);
int			calc_moves_to_push_element_onto_a(t_list *a, t_list *b, t_list *push_candidate);
t_list		*get_biggest_element_smaller_than_candidate(t_list *a, t_list *push_candidate);
t_list		*get_smallest_element_bigger_than_candidate(t_list *a, t_list *push_candidate);
#endif //PUSH_SWAP_H
