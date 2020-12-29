#ifndef COMMAND_H
# define COMMAND_H

# include "signal_handler.h"
# include <sys/fcntl.h>
# include <dirent.h>
# include <sys/stat.h>

/*
** redirection.c
*/
int			find_file_fd(t_redir *redir);
/*
** cd.c
*/
bool	cd(t_cmd_line *cmd_line);
t_list	*find_env_target_list(char *target);
void	set_env_target(char *target, char *value);
/*
** echo.c
*/
bool	echo(t_cmd_line *cmd_line);
/*
** export.c
*/
char	*export(t_cmd_line *cmd_line);
/*
** run_command.c
*/
bool	run_command(t_cmd_line *cmd_line);
/*
** pwd.c
*/
bool	pwd(t_cmd_line *cmd_line);
/*
** ft_exit.c 
*/
char	*ft_exit(t_cmd_line *cmd_line);

char	*search_file(char *file_name);




#endif