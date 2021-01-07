/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dokang <dokang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 17:14:59 by dokang            #+#    #+#             */
/*   Updated: 2021/01/07 17:15:00 by dokang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
void			close_pipe_fd(t_pipes *pipes);

/*
** set_pipe.c
*/
bool			init_pipe(t_pipes *pipes);
void			swap_pipe(t_pipes *pipes);
void			set_pipe_flag(t_cmd_line *cmd_line, bool *pipe_flag);
bool			set_pipe(t_cmd_line *cmd_line, bool flag, \
							t_pipes *pipes);
#endif
