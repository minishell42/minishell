#ifndef COMMAND_H
# define COMMAND_H

# include "signal_handler.h"
# include <sys/fcntl.h>

bool	redirection(t_cmd_line *cmd_line, t_list *env, char *res);
char	*echo(t_cmd_line *cmd_line, t_list *env, char *pipe_input);
char	*run_command(t_cmd_line *cmd_line, t_list *env);
char	*export(t_cmd_line *cmd_line, t_list *env, char* pipe_input);
t_list	*find_env_target_list(t_list *env, char *target);

char	*cd(t_cmd_line *cmd_line, t_list *env, char *pipe_flag);
void	set_env_target(t_list *env, char *target, char *value);
char	*pwd(t_cmd_line *cmd_line, char **pipe_flag);


char	*ft_exit(t_cmd_line *cmd_line, t_list *env, char **pipe_input);

#endif