# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dokang <dokang@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/07 13:17:38 by dokang            #+#    #+#              #
#    Updated: 2020/11/07 13:17:38 by dokang           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS = -Wall -Wextra -Werror

SRC = *.c

NAME = libft.a

OBG = ${SRC:.c=.o}

all : $(NAME)

$(NAME) : $(OBG)
	ar rc $(NAME) $(OBG)
	ranlib $(NAME)

.c.o :
	$(CC) $(CFLAGS) -c $(SRC)

bonus : $(OBG)
	$(CC) $(CFLAGS) -c $(SRC)
	ar rc $(NAME) $(OBG)

fclean :
	rm -f $(NAME)

clean :
	rm -f *.o

re : fclean all clean
