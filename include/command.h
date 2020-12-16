#ifndef COMMAND_H
# define COMMAND_H

# include "parsing.h"
# include <sys/fcntl.h>

bool	redirection(t_cmd_line *cmd_line, t_list *env, char *res);
char	*echo(t_cmd_line *cmd_line, t_list *env, char *pipe_input);
char	*run_command(t_cmd_line *cmd_line, t_list *env);

char	*cd(t_cmd_line *cmd_line, t_list *env, char *pipe_flag);
void	set_env_target(t_list *env, char *target, char *value);


#endif