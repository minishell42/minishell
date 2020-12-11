#ifndef MINISHELL_H
# define MINISHEL_H

# include "command.h"

void				excute(t_cmd_line *cmd_line, char *envp[]);
void				echo(t_cmd_line *cmd_line, char *envp[]);
t_list 				*get_env_llist(char *envp[]);

#endif
