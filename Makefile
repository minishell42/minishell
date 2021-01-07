CC			= gcc

INCLUDE		= include/

CFLAGS		= -I$(INCLUDE) 

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
				validate_line.c \
				free_struct.c \
				make_param_list.c \
				convert_quote_str.c \
				set_redir_struct.c \
				change_to_absolute_path.c \
				tilde_expansion.c \
				set_tilde_case.c
PARSE		= $(addprefix $(PARSE_DIR), $(PARSE_SRCS))

COMMAND_DIR		= command/
COMMAND_SRCS	= echo.c \
					run_command.c \
					cd.c \
					pwd.c \
					export.c \
					ft_exit.c \
					search_file.c \
					env.c \
					unset.c \
					exp_key_value.c \
					exp_env_key.c \
					exp_utils.c \
					cd_set_dir.c \
					run_operator_command.c
COMMAND			= $(addprefix $(COMMAND_DIR), $(COMMAND_SRCS))

SIGNAL_DIR		= signal/
SIGNAL_SRCS		= signal_handler.c \
					set_prompt.c
SIGNAL			= $(addprefix $(SIGNAL_DIR), $(SIGNAL_SRCS))

PIPE_DIR		= pipe/
PIPE_SRCS		= fd_handler.c \
					set_pipe.c
PIPE			= $(addprefix $(PIPE_DIR), $(PIPE_SRCS))

UTILS_DIR	= utils/
UTILS_SRCS	= string_util.c \
				check_character.c \
				env_llist.c 
UTILS		= $(addprefix $(UTILS_DIR), $(UTILS_SRCS))

ERROR_DIR	= error/
ERROR_SRCS	= error.c \
				built_in_error.c \
				syntax_error.c
ERROR		= $(addprefix $(ERROR_DIR), $(ERROR_SRCS))

FILES		= minishell.c
FILES		+= $(GNL)
FILES		+= $(PARSE)
FILES		+= $(COMMAND)
FILES		+= $(UTILS)
FILES		+= $(ERROR)
FILES		+= $(SIGNAL)
FILES		+= $(PIPE)

SRC			= main.c
SRC			+= $(FILES)

OBJS		= $(SRC:.c=.o)
NAME		= minishell 

TEST		= test
TEST_DIR	= test_case/
TEST_FILES	= test.c \
				test_validate_line.c \
				test_export.c \
				test_env.c \
				test_unset.c
				
TEST_SRC 	= $(addprefix $(TEST_DIR), $(TEST_FILES))
TEST_SRC	+= $(FILES)

TEST_OBJS	= $(TEST_SRC:.c=.o)

all: 
	make -C libft
	make $(NAME)
	./$(NAME)

$(NAME) : $(OBJS)
	$(CC) -fsanitize=address -o $(NAME) $(OBJS) $(LIBFTFLAG)

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
