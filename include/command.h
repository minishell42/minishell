#ifndef COMMAND_H
# define COMMAND_H

# include "signal_handler.h"
# include <sys/stat.h>

typedef	struct	s_export
{
	char		*env_key;
	char		*env_value;
	bool		end_in_plus;
	char		**key_values;
	char		*key_value;
	bool		has_separator;
}				t_export;

/*
** cd_set_dir.c
*/
char			*set_dir(t_list *param_list, bool *flag);

/*
** cd.c
*/
bool			cd(t_cmd_line *cmd_line);

/*
** echo.c
*/
bool			echo(t_cmd_line *cmd_line);
char			*make_param_str(t_list *param_list);

/*
** export.c
*/
bool			export(t_cmd_line *cmd_line);

/*
** exp_utils.c
*/
void			print_content_exp(void *content);
void			free_export(t_export *exp_info);

/*
** exp_key_value.c
*/
char			*join_key_value(char *env_key, char *key_value);
bool			validate_key_value(char *key_value, t_cmd_line *cmd_line);
char			*get_value(char *str);
t_list			*find_env_target_list(char *target);
void			set_env_target(char *target, char *value);

/*
** exp_env_key.c
*/
char			*get_env_key(char *param, \
							t_cmd_line *cmd_line, t_export *exp_info);

/*
** run_command.
*/
bool			run_command(t_cmd_line *cmd_line);
bool			run_normal_cmd(t_cmd_line *cmd_line, \
							t_pipes *pipes, bool *pipe_flag);
/*
** run_operator_command.c
*/
bool			check_env_operator_cmd(t_cmd_line *cmd_line);
bool			run_env_operator_cmd(t_cmd_line *cmd_line, \
									t_pipes *pipes, bool *pipe_flag);
/*
** pwd.c
*/
bool			pwd(t_cmd_line *cmd_line);

/*
** ft_exit.c
*/
char			*ft_exit(t_cmd_line *cmd_line);

/*
** env.c
*/
bool			ft_env(t_cmd_line *cmd_line);
void			print_content(void *content);

/*
** unset.c
*/
bool			ft_unset(t_cmd_line *cmd_line);

/*
** search_file.c
*/
char			*search_file(t_cmd_line *cmd_line, char *file_name);

#endif
