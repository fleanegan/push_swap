HEAD				= push_swap.h \
					  libft/libft.h \
					  libft/libft_auxilliar.h \

SRCS				= ./markup_is_swap_advantage.c \
                      ./stack_operations_low_level_rotate.c \
                      ./russian_algorithm_move_unmarked_to_b.c \
                      ./count_moves.c \
                      ./parsing.c \
                      ./russian_algorithm_move_b_back_to_a_auxiliary.c \
                      ./main.c \
                      ./stack_operations_low_level_reverse_rotate.c \
                      ./allocating.c \
                      ./markup_calc_reference.c \
                      ./misc.c \
                      ./russian_algorithm_move_b_back_to_a.c \
                      ./stack_operations_low_level_swap.c \
                      ./stack_operations_high_level.c \
                      ./stack_operations_low_level_push.c \
                      ./markup.c \
                      ./stack_indexing.c \
                      ./stack_operations_low_level_circular.c \

OBJS				= $(SRCS:.c=.o)

NAME				= push_swap

CC					= gcc

CFLAGS				= -Wall -Werror -Wextra

RM					= rm -f

ILIBFT				= -L./libft -I./libft -lft

CFLAGS				= -Wall -Wextra -Werror

.c.o:
					$(CC) $(CFLAGS) -c $< -o $(<:.c=.o) -I. -I./libft

${NAME}:			$(OBJS) $(HEAD)
					$(MAKE) -C  ./libft/ all
					${CC} ${CFLAGS} $(OBJS) -o $(NAME) $(ILIBFT) -I. -I./libft

all:				${NAME}

debug:				$(SRCS) $(HEAD)
					$(MAKE) -C  ./libft/ all
					${CC} ${CFLAGS} -g -o $(NAME) $(SRCS) $(ILIBFT)

clean:
					$(MAKE) -C  ./libft/ clean
					${RM} ${OBJS}

fclean:
					$(MAKE) -C  ./libft/ fclean
					${RM} ${NAME}

re:					fclean all

.PHONY: clean all re


