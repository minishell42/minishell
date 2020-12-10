CC			=gcc

INCLUDE		= include/

CFLAGS		=-I$(INCLUDE)

LIB			= libft/

LIBFTFLAG	= -L$(LIB) -lft

GNL_DIR		= get_next_line/
GNL_SRCS	= get_next_line.c \
				get_next_line_utils.c
GNL			= $(addprefix $(GNL_DIR), $(GNL_SRCS))

PARSE_DIR	= parsing/
PARSE_SRCS	= check_value.c \
				get_command_lines.c \
				parse_cmd_line.c \
				set_env_value.c \
				set_redirection_value.c
PARSE		= $(addprefix $(PARSE_DIR), $(PARSE_SRCS))

UTILS_DIR	= utils/
UTILS_SRCS	= error.c \
				string_util.c
UTILS		= $(addprefix $(UTILS_DIR), $(UTILS_SRCS))

FILES		= env_llist.c
FILES		+= $(GNL)
FILES		+= $(PARSE)
FILES		+= $(UTILS)

SRC			= main.c
SRC			+= $(FILES)

OBJS		= $(SRC:.c=.o)
NAME		= minishell 

TEST		= test
TEST_DIR	= test_case/
TEST_FILES	= test.c \
				test_get_command_line.c
TEST_SRC 	= $(addprefix $(TEST_DIR), $(TEST_FILES))
TEST_SRC	+= $(FILES)

TEST_OBJS	= $(TEST_SRC:.c=.o)

all: 
	make -C libft
	make $(NAME)
	./$(NAME)

$(NAME) : $(OBJS)
	$(CC) -fsanitize=address -lasan -o $(NAME) $(OBJS) $(LIBFTFLAG)

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

tclear:
	clear

rt: tclear
	make -C libft
	make $(TEST)
	rm -f $(OBJS)
	rm -rf $(TEST_OBJS)
	make clean -C libft
	rm -f $(NAME)
	make fclean -C libft
	./$(TEST)
	rm -rf $(TEST)