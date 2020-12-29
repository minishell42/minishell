#ifndef	PARSING_H
# define PARSING_H

# include "utils.h"
# include "get_next_line.h"

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

/*
** check_value.c
*/
bool				check_character_in_line(char *line, int *index, int (*func)());
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
int					set_param(t_cmd_line *command_line, char *start);
bool				change_param_value(t_cmd_line *cmd_line);
char				*convert_to_valid_value(char *start, int len);
/*
** set_env_value.c
*/
char 				*get_env_value(char *target_key);
void 				join_env_value(char **ret, char *str, int *i);
char				*set_multi_env(char *str);
char				*change_to_absolute_path(char *value);
/*
** set_redirection_value.c
*/
void				set_redirection_flag(t_cmd_line *cmd_line, int *i);
bool				set_redirection_param(t_cmd_line *cmd_line);
/*
** validate_line.c
*/
int					validate_line(char *line);

t_list	*make_param_list(char *param);


#endif