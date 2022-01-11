SRCS				= $(shell find ./src/ -type f -name "*.c")

TEST_HEADERS		= $(shell find ./test -type f -name "*.h")

TEST_SOURCES		= $(shell find ./test -type f -name "*.c")

ICRITERION			= -L./criterion-v2.3.3/lib -I./criterion-v2.3.3/include -lcriterion -Wl,-rpath=./criterion-v2.3.3/lib

alibi_compile:	$(SRCS) $(TEST_SOURCES) $(TEST_HEADERS)
	@echo $(SRCS) $(TEST_SOURCES) $(ICRITERION) -Itest -Isrc/libft -Isrc
	@gcc $(SRCS) $(TEST_SOURCES) $(ICRITERION) -Itest -Isrc/libft -Isrc
	@rm a.out

run_tests:
			$(MAKE) -C 	./test/ run
re:
			$(MAKE) -C 	./test/ re

fclean:
			$(MAKE) -C 	./test/ fclean

all:
			$(MAKE) -C 	./test/ all

own_tests:
			$(MAKE) -C 	./test/ test_own

