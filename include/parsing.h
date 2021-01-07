#ifndef PARSING_H
# define PARSING_H

# include "utils.h"
# include "get_next_line.h"
# include <sys/types.h>
# include <dirent.h>

# define EXCUTABLE 1
# define ECHO 2
# define CD 3
# define PWD 4
# define EXPORT 5
# define UNSET 6
# define ENV 7
# define EXIT 8

# define OUT_OVERRIDE 1
# define REDIR_IN 2
# define OUT_ENDLINE 3

typedef struct		s_redir
{
	int				redir_flag;
	char			*redir_param;
	int				file_fd;
}					t_redir;

typedef struct		s_command_line
{
	char			*command;
	char			*option;
	t_list			*param;
	int				command_num;
	bool			pipe_flag;
	t_list			*redir_param;
}					t_cmd_line;

t_list				*g_env;

/*
** free_struct.c
*/
void				free_cmd_struct(t_cmd_line *cmd);
void				free_env_list(t_list **env);
void				close_redir_file(t_cmd_line *cmd);

/*
** check_value.c
*/
bool				check_character_in_line(char *line, \
											int *index, int (*func)());
bool				check_redirection(t_cmd_line *cmd_line);
bool				check_cmd_num(t_cmd_line *cmd_line);

/*
** get_command_lines.c
*/
t_cmd_line			*get_command_line(char **line_ptr);

/*
** parse_command.c
*/
bool				parse_command(t_cmd_line *cmd_line, char *start, int len);
int					get_command_num(char *command);

/*
** parse_param.c
*/
char				*set_value_before_quote(char *str, int *index);
char				*convert_to_valid_value(char *start, int len);
int					set_param(t_cmd_line *command_line, char *start);

/*
** set_env_value.c
*/
char				*get_env_value(char *target_key);
char				*set_multi_env(char *str);

/*
** set_redirection_value.c
*/
bool				set_redirection_param(t_cmd_line *cmd_line);

/*
** validate_line.c
*/
int					validate_line(char *line);
void				set_special_param(t_cmd_line *cmd_line);

/*
** convert_to_quote.c
*/
char				*convert_to_quote_str(char *str, int *index);

/*
** apply_absolute_path.c
*/
char				*change_to_absolute_path(char *value);
/*
** tilde_expansion.c
*/
char				*apply_tilde_expansion(char *before_str);
char				*set_tilde_dir(char *user_name);

/*
** set_redir_struct.c
*/
bool				can_make_redir_list(t_cmd_line *cmd_line, \
										char *content);

/*
** change_to_absolute_path.c
*/
char				*change_to_absolute_path(char *value);
t_list				*make_param_list(char *param);

/*
** set_tilde_case.c
*/
char				*tilde_expansion_dir(void);
char				*set_tilde_case2(char *before_str);
char				*set_tilde_case3(char *before_str);
char				*set_tilde_case4(char *before_str);
char				*set_tilde_case5(char *before_str);

#endif
