CC=gcc
CFLAGS=-I./include
LIBFTFLAG = -L./libft -lft
FILES =	get_next_line/get_next_line.c \
	get_next_line/get_next_line_utils.c \
	parsing.c \
	error.c \
	env_llist.c
SRC = main.c
SRC += $(FILES)

OBJS = $(SRC:.c=.o)
NAME = minishell 

TEST = test
TEST_DIR = test_case/
TEST_FILES = test.c \
				test_get_command_line.c
TEST_SRC = $(addprefix $(TEST_DIR), $(TEST_FILES))
TEST_SRC += $(FILES)

TEST_OBJS = $(TEST_SRC:.c=.o)

all: 
	make -C libft
	make $(NAME)
	./$(NAME)

$(NAME) : $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(LIBFTFLAG)

clean :
	rm -f $(OBJS)
	rm -rf $(TEST_OBJS)
	make clean -C libft

fclean: clean
	rm -f $(NAME)
	rm -rf $(TEST)
	make fclean -C libft

re: fclean all

$(TEST) : $(TEST_OBJS)
	$(CC) $(CFLAGS) -o $(TEST) $(TEST_OBJS) $(LIBFTFLAG)

t:
	make -C libft
	make $(TEST)
	./$(TEST)
	