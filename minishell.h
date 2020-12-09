#ifndef MINISHELL_H
# define MINISHEL_H

# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>
# include <sys/wait.h>

# include "get_next_line.h"
# include "libft.h"

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

void				message_and_exit(char *message, bool built_in_error);
t_cmd_line			*get_command_line(char **line_ptr,  char *quot_flag, t_list *env);
t_list				*get_command_lines(char *line, t_list *env);
char				*get_param(char *start);
void				excute(t_cmd_line *cmd_line, char *envp[]);
void				echo(t_cmd_line *cmd_line, char *envp[]);
bool				set_option(t_cmd_line *cmd_line, char **splited_line);
int 				get_command_num(char *command);
t_list				*get_env_llist(char *envp[]);


#endif
