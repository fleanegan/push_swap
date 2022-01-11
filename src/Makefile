HEAD				= $(shell find ./ -type f -name "*.h")

SRCS				= $(shell find ./ -maxdepth 1 -type f -name "*.c")

#OBJS				= $(SRCS:.c=.o)

NAME				= push_swap

CC					= gcc

RM					= rm -f

ILIBFT				= -L./libft -I./libft -lft

CFLAGS				= -Wall -Wextra -Werror

${NAME}:			$(SRCS) $(HEAD)
					$(MAKE) -C  ./libft/ all
					${CC} ${CFLAGS} -o $(NAME) $(SRCS) $(ILIBFT)

all:				${NAME}

clean:
					$(MAKE) -C  ./libft/ clean
					${RM} ${OBJS}

fclean:
					$(MAKE) -C  ./libft/ fclean
					${RM} ${NAME}

re:					fclean all

.PHONY: clean all re


