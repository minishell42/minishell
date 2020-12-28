#ifndef COMMAND_H
# define COMMAND_H

# include "signal_handler.h"
# include <sys/fcntl.h>
# include <dirent.h>
# include <sys/stat.h>

/*
** redirection.c
*/
int			find_file_fd(t_redir *redir, t_list *env);
/*
** cd.c
*/
bool	cd(t_cmd_line *cmd_line, t_list *env);
t_list	*find_env_target_list(t_list *env, char *target);
void	set_env_target(t_list *env, char *target, char *value);
/*
** echo.c
*/
bool	echo(t_cmd_line *cmd_line, t_list *env);
/*
** export.c
*/
bool	export(t_cmd_line *cmd_line, t_list *env, char* pipe_input);
/*
** run_command.c
*/
bool	run_command(t_cmd_line *cmd_line, t_list *env);
/*
** pwd.c
*/
bool	pwd(t_cmd_line *cmd_line);
/*
** ft_exit.c 
*/
char	*ft_exit(t_cmd_line *cmd_line, t_list *env);

char	*search_file(char *file_name, t_list *env);




#endif