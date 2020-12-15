#ifndef COMMAND_H
# define COMMAND_H

# include "parsing.h"

bool	ft_cd(t_cmd_line *cmd_line, t_list *env, bool *pipe_flag);
void	set_env_target(t_list *env, char *target, char *value);


#endif