#include "minishell.h"

int			get_command_num(char *command)
{
    if (are_equal(command, "echo"))
	{
        return (ECHO);
	}
	// exit?
    return (0);
}



bool		is_option(char *str)
{
		

}

bool		set_option(t_cmd_line *cmd_line, char **splited_line)
{
	int			count;
	char		*option;

	count = 0;
	while (splited_line[count])
		count++;
	is_option(splited_line[1]);
	return (true);
}

t_cmd_line	*get_command_line(char *line)
{
	char		**splited_line;
	char		*command;
    char		*option;
	t_cmd_line	*ret;

	ret = ft_calloc(1, sizeof(t_cmd_line));

	splited_line = ft_split(line, ' ');
	ret->command = splited_line[0];
	ret->command_num = get_command_num(ret->command);
	if (ret->command_num == ECHO)
	{
		set_option(ret, splited_line);

	}
	else
		ret->param = splited_line[1];

	printf("command = %s\n", ret->command);
	printf("param = %s\n", ret->param);
	return (ret);
}

void		echo(t_cmd_line *cmd_line, char *envp[])
{
	int			pid;
	int			status;
	
	pid  = fork();
	if (pid > 0)
		waitpid(pid, NULL, 0);
	else if (pid == 0)
		execve("/usr/bin/lessecho", &cmd_line->param, envp);
	else
		exit(0);	
}

void		excute(t_cmd_line *cmd_line, char *envp[])
{
	if (cmd_line->command_num == ECHO)
		echo(cmd_line, envp);
}

char		*get_str_in_quotation_set(char *str)
{
	
}



int			main(int argc, char **argv, char *envp[])
{
	char		*line;
	char		**command_lines;
	int			command_num;
	t_cmd_line	*command_line;

	while (true)
	{
		write(1, "minishell$ ", 12);
		get_next_line(0, &line);
		command_lines = ft_split(line, ';');
		int i = 0;
		while (command_lines[i])
		{
			command_line = get_command_line(command_lines[i]);
			excute(command_line, envp);
			i++;
		}
	}
}