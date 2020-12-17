#ifndef COMMAND_H
# define COMMAND_H

# include "signal_handler.h"
# include <sys/fcntl.h>

bool	redirection(t_cmd_line *cmd_line, t_list *env, char *res);
char	*echo(t_cmd_line *cmd_line, t_list *env, char *pipe_input);
char	*run_command(t_cmd_line *cmd_line, t_list *env);

char	*ft_exit(t_cmd_line *cmd_line, t_list *env, char **pipe_input);

#endif