#ifndef PIPE_H
# define PIPE_H

# define READ 0
# define WRITE 1

# include "parsing.h"
# include <sys/fcntl.h>

typedef struct	s_pipe_fd
{
	int		old[2];
	int		new[2];
}				t_pipes;

/*
** fd_handler.c
*/
void			close_write_fd(t_pipes *pipes);
int				get_write_fd(t_pipes *pipes);
int				get_read_fd(t_pipes *pipes);
int				find_file_fd(t_redir *redir);

/*
** set_pipe.c
*/
bool			init_pipe(t_pipes *pipes);
void			swap_pipe(t_pipes *pipes);
void			set_pipe_flag(t_cmd_line *cmd_line, bool *pipe_flag);
bool			set_pipe(t_cmd_line *cmd_line, bool flag, \
							t_pipes *pipes);
#endif