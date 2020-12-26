#ifndef ERROR_H
# define ERROR_H

# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <errno.h>


# include "libft.h"

# define ALLOC_ERROR 1
# define QUOT_IS_NOT_PAIR 2
# define INVALID_COMMAND 3
# define TOO_MANY_REDIR 4
# define SYNTAX_ERROR 5
# define PARAM_IS_NEWLINE 6
# define INVALID_EXPORT_PARAM 7

typedef struct	s_error 
{
	int		err_number;
	char	*err_value;
}				t_error;

t_error			g_err;

/*
** error.c
*/
void			message_and_exit(char *message, bool built_in_error);
void			print_err_msg(void);
bool			parsing_err_value(int error_number, char *error_point);
void			set_quot_err(char quot_flag);
int				set_syntax_err(char *line, int i);

/*
** built_in_error.c
*/
void			built_in_error(void);



# endif