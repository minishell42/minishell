#ifndef COMMAND_H
# define COMMAND_H

# include "parsing.h"
# include <sys/fcntl.h>

bool	redirection(t_cmd_line *cmd_line, t_list *env, char *res);
char	*echo(t_cmd_line *cmd_line, t_list *env, char *pipe_input);
char	*run_command(t_cmd_line *cmd_line, t_list *env);
char	*export(t_cmd_line *cmd_line, t_list *env, char* pipe_input);
t_list	*find_env_target_list(t_list *env, char *target);

#endif