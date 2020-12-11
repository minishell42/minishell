#ifndef ERROR_H
# define ERROR_H

# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>
# include <sys/wait.h>

# include "libft.h"

# define ALLOC_ERROR -1
# define QUOT_IS_NOT_PAIR -2
# define INVALID_COMMAND -3
# define TOO_MANY_REDIR -4

typedef struct	s_error 
{
	int		err_number;
	char	*err_value;
}				t_error;

t_error		g_err;

void		message_and_exit(char *message, bool built_in_error);
void		print_err_msg(char error_flag);
bool		parsing_err_value(int error_number, char *error_point);

# endif