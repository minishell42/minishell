#ifndef MINISHELL_H
# define MINISHEL_H

# include "command.h"


typedef struct	s_pipe_fd
{
	int		old[2];
	int		new[2];
}				t_pipes;

void				excute(t_cmd_line *cmd_line, char *envp[]);
t_list 				*get_env_llist(char *envp[]);
/*
** minishell.c
*/
void				minishell(char *line);

#endif
