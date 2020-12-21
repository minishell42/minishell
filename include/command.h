#ifndef COMMAND_H
# define COMMAND_H

# include "signal_handler.h"
# include <sys/fcntl.h>

/*
** redirection.c
*/
void	check_and_set_redir_out(t_cmd_line *cmd_line, t_list *env, char *buf, int *pipe_fd);
void	check_and_set_redir_in(t_cmd_line *cmd_line, t_list *env, char *buf);
/*
** cd.c
*/
char	*cd(t_cmd_line *cmd_line, t_list *env, char *pipe_flag);
t_list	*find_env_target_list(t_list *env, char *target);
void	set_env_target(t_list *env, char *target, char *value);
/*
** echo.c
*/
char	*echo(t_cmd_line *cmd_line, t_list *env, char *pipe_input);
/*
** export.c
*/
char	*export(t_cmd_line *cmd_line, t_list *env, char* pipe_input);
/*
** run_command.c
*/
char	*run_command(t_cmd_line *cmd_line, t_list *env, char *pipe_input);
/*
** pwd.c
*/
char	*pwd(t_cmd_line *cmd_line, char **pipe_flag);
/*
** ft_exit.c 
*/
char	*ft_exit(t_cmd_line *cmd_line, t_list *env, char **pipe_input);




#endif