CC=gcc
CFLAGS=-I./include
LIBFTFLAG = -L./libft -lft
SRC = main.c \
	get_next_line/get_next_line.c \
	get_next_line/get_next_line_utils.c
OBJS = $(SRC:.c=.o)
NAME = minishell 

all: 
	make -C libft
	make $(NAME)
	./$(NAME)

$(NAME) : $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(LIBFTFLAG)

clean :
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)
	make fclean -C libft

re: fclean all