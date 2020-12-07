#ifndef MINISHELL_H
# define MINISHEL_H

# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>
# include <sys/wait.h>

# include "get_next_line.h"
# include "libft.h"

# define ECHO 1

typedef struct		s_command_line
{
    char			*command;
    char			*option;
    char			*param;
	int				command_num;
}					t_cmd_line;

void				message_and_exit(char *message, bool built_in_error);
t_cmd_line			*get_command_line(char **line_ptr);
t_list				*get_command_lines(char *line);
char				*get_param(char *start);
void				excute(t_cmd_line *cmd_line, char *envp[]);
void				echo(t_cmd_line *cmd_line, char *envp[]);
bool				set_option(t_cmd_line *cmd_line, char **splited_line);
int 				get_command_num(char *command);

#endif
