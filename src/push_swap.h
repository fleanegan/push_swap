/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h					                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <fschlute>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 09:00:50 by                   #+#    #+#             */
/*   Updated: 2021/11/23 09:00:59 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
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

enum e_markup_mode {index_mode, value_mode};

// russian algorithm
void			markup_one_element(\
				t_list *element_to_be_marked_up, \
				int *global_max, enum e_markup_mode mode);
t_list			*calc_markup_reference(\
				t_meta_stack *meta_stack, enum e_markup_mode mode);
void			markup_stack_by_reference(\
				t_meta_stack *meta_stack, \
				t_list *reference, enum e_markup_mode mode);
int				count_markups(const t_list *stack);
int				count_elements_to_be_moved_to_b(t_meta_stack *a);
int				is_swapping_a_good_idea(\
				t_meta_stack *meta_stack, \
				t_list *markup_reference, enum e_markup_mode mode);
void			russian_algorithm_move_unmarked_to_b(\
				t_meta_stack *a, t_meta_stack *b, \
				t_list **history, enum e_markup_mode mode);
t_list			*find_next_element_to_push(t_meta_stack *a, t_meta_stack *b);
void			russian_algorithm_move_b_back_to_a(\
				t_meta_stack *a, t_meta_stack *b, t_list **history);
t_list			*russian_algorithm(\
				t_meta_stack *a, enum e_markup_mode markup_mode);

// parsing
int				is_str_parsable(char *in);
t_content		*parse_one_string(char *in);
int				does_fit_into_int(const char *in);
int				is_dubl(t_list *stack, int compare_value);
t_meta_stack	*generate_stack(int argc, const char **argv);

// stack operations
void			push_first_element_to_the_other_stack(\
				t_meta_stack *a, t_meta_stack *b, t_list **history);

void			swap_first_two_elements(\
				t_meta_stack *meta_stack, t_list **history);
void			reverse_rotate(t_meta_stack *meta_stack, t_list **history);
void			rotate(t_meta_stack *meta_stack, t_list **history);
void			rotate_stack_n_steps(\
				t_meta_stack *meta_stack, int steps, t_list **history);
void			move_to_top(\
				t_meta_stack *meta_stack, \
				t_list *element_to_move, t_list **history);
int				calc_moves_to_top(t_meta_stack *meta_stack, t_list *element);
int				calc_moves_to_bottom(t_meta_stack *meta_stack, t_list *element);
int				calc_moves_to_get_a_in_push_position(\
				t_meta_stack *a, t_list *push_candidate);
void			bring_a_in_push_position(\
				t_meta_stack *a, t_list *push_candidate, t_list **history);
int				calc_moves_to_push_element_onto_a(\
				t_meta_stack *a, t_meta_stack *b, t_list *push_candidate);
t_list			*get_biggest_element_smaller_than_candidate(\
				t_list *a, int value_of_candidate);
t_list			*get_smallest_element_bigger_than_candidate(\
				t_list *a, int value_of_candidate);
void			rotate_a_back_in_order(t_meta_stack *a, t_list **history);

// utility functions
void			*shallow_copy(void *content);
t_content		*get_content_of_element(t_list *in);
void			do_not_free_content(void *content);
void			close_stack_ring(t_list *stack, t_list *last_element);
void			open_stack_ring(t_list *stack, t_list *last_element);
int				sorting_index_equals_to(void *content, int index);
t_meta_stack	*new_meta_stack(void);
void			index_stack(t_list *stack);
t_content		*new_stack_content(int in);

#endif //PUSH_SWAP_H
