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
				parse_command.c \
				parse_param.c \
				set_env_value.c \
				set_redirection_value.c \
				validate_line.c
PARSE		= $(addprefix $(PARSE_DIR), $(PARSE_SRCS))

COMMAND_DIR		= command/
COMMAND_SRCS	= echo.c \
					export.c \
					redirection.c \
					run_command.c \
					cd.c
COMMAND			= $(addprefix $(COMMAND_DIR), $(COMMAND_SRCS))

UTILS_DIR	= utils/
UTILS_SRCS	= string_util.c \
				check_character.c
UTILS		= $(addprefix $(UTILS_DIR), $(UTILS_SRCS))

ERROR_DIR	= error/
ERROR_SRCS	= error.c
ERROR		= $(addprefix $(ERROR_DIR), $(ERROR_SRCS))

FILES		= env_llist.c \
				minishell.c
FILES		+= $(GNL)
FILES		+= $(PARSE)
FILES		+= $(COMMAND)
FILES		+= $(UTILS)
FILES		+= $(ERROR)

SRC			= main.c
SRC			+= $(FILES)

OBJS		= $(SRC:.c=.o)
NAME		= minishell 

TEST		= test
TEST_DIR	= test_case/
TEST_FILES	= test.c \
				test_get_command_line.c \
				test_get_command_lines.c \
				test_cd.c \
				test_validate_line.c \
				test_redirection.c
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
	$(CC) -fsanitize=address -lasan $(CFLAGS) -o $(TEST) $(TEST_OBJS) $(LIBFTFLAG)

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