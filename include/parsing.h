#ifndef	PARSING_H
# define PARSING_H

# include "utils.h"
# include "get_next_line.h"

# define ECHO 1
# define OUT_OVERRIDE 1
# define REDIR_IN 2
# define OUT_ENDLINE 3

typedef struct		s_command_line
{
	char			*command;
	char			*option;
	char			*param;
	int				command_num;
	bool			pipe_flag;
	int				redir_flag;
	t_list			*redir_param;
}					t_cmd_line;

/*
** check_value.c
*/
int			is_separator(int c);
int			is_redirection(int c);
int			is_semicolon(int c);
bool		check_character_in_line(char *line, int *index, int (*func)());
// void		check_chacter_in_line(char *line, int *index, char *quot_flag, int (*func)());
bool		check_redirection(t_cmd_line *cmd_line);
// int			check_redirection(t_cmd_line *cmd_line);
/*
** get_command_lines.c
*/
t_cmd_line	*get_command_line(char **line_ptr, t_list *env);
// t_cmd_line	*get_command_line(char **line_ptr, char *quot_flag, t_list *env);
t_list		*get_command_lines(char *line, t_list *env);
/*
** parse_cmd_line.c
*/
int			get_command_num(char *command);
int			set_param(t_cmd_line *command_line, char *start, t_list *env);
bool		parse_command(t_cmd_line *cmd_line, char *start, int len, t_list *env);
// bool		parse_command(t_cmd_line *cmd_line, char *start, int len, t_list *env);
bool		change_param_value(t_cmd_line *cmd_line, t_list *env);
char		*convert_to_valid_value(char *start, int len, t_list *env);
/*
** set_env_value.c
*/
char 		*get_env_value(char *target_key, t_list *env);
void 		join_env_value(char **ret, char *str, int *i, t_list *env);
char		*set_multi_env(char *str, t_list *env);

char		*change_to_absolute_path(char *value, t_list *env);

/*
** set_redirection_value.c
*/
void		set_redirection_flag(t_cmd_line *cmd_line, int *i);
bool		set_redirection_param(t_cmd_line *cmd_line, t_list *env);
// char		*set_redirection_param(t_cmd_line *cmd_line, t_list *env);


#endif