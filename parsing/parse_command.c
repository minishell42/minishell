#include "parsing.h"

int	get_command_num(char *command, t_list *env)
{
    if (are_equal(command, "echo"))
		return (ECHO);
	else if (are_equal(command, "cd"))
		return (CD);
	else if (are_equal(command, "pwd"))
		return (PWD);
	else if (are_equal(command, "export"))
		return (EXPORT);
	else if (are_equal(command, "unset"))
		return (UNSET);
	else if (are_equal(command, "env"))
		return (ENV);
	else if (are_equal(command, "exit"))
		return (EXIT);
	return (0);
}

static bool	parse_cmd(t_cmd_line *cmd_line, char *value, t_list *env)
{
	char *temp;
	
	if (temp = change_to_absolute_path(value, env))
	{
		cmd_line->command = temp;
		cmd_line->command_num = EXCUTABLE;
		free(value);
	}
	else
		cmd_line->command = value;
	if (!cmd_line->command_num)
		cmd_line->command_num = get_command_num(cmd_line->command, env);
	return (true);
}

bool		parse_command(t_cmd_line *cmd_line, char *start, int len, t_list *env)
{
	char	*value;

	value = convert_to_valid_value(start, len, env);
	if (!cmd_line->command)
	{
		if (value[0] ==  '>' || value[0] == '<')
		{
			value[0] = 0;
			cmd_line->command = value;
			return (false);
		}
		return (parse_cmd(cmd_line, value, env));
	}
	else if (cmd_line->command_num == ECHO && are_equal(value, "-n"))
	{
		if (!cmd_line->option)
			cmd_line->option = value;
		else
			free(value);
		return (true);
	}
	free(value);
	return (false);
}
