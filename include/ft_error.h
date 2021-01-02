#ifndef FT_ERROR_H
# define FT_ERROR_H

# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <errno.h>
# include <sysexits.h>

# include "libft.h"

# define SYNTAX_ERROR 2
# define TOO_MANY_REDIR 4
# define QUOT_IS_NOT_PAIR 5
# define PARAM_IS_NEWLINE 6
# define INVALID_EXPORT_PARAM 7
# define TOO_MANY_REDIR_PARAM 8
# define NO_FILE_OR_DIRECTORY 9
# define NO_OLDPWD 10
# define NO_HOME 11
# define NOT_OPEN 12

# define INVALID_COMMAND 127
# define INVALID_ARGUMENT_TO_EXIT 128

typedef struct	s_error
{
	char	*err_value;
}				t_error;

t_list			*g_err;
int				g_exit_code;

/*
** error.c
*/
void			message_and_exit(char *message, bool built_in_error);
void			print_err_msg(void);
char			*get_err_msg(int err_number);

/*
** built_in_error.c
*/
void			built_in_error(void);
void			set_exit_status(int exit_code);
void			make_err_msg(int exit_code, char *cmd, char *value, char *msg);

/*
** syntax_error.c
*/
void			set_quot_err(char quot_flag);
int				set_syntax_err(char *line, int i);

#endif
