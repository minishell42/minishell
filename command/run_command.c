#include "command.h"

void	free_pipe_input(char **pipe_input)
{
	if (*pipe_input)
		free(*pipe_input);
	*pipe_input = NULL;
}

char	*run_command(t_cmd_line *cmd_line, t_list *env)
{
	char		*result;
	static char	*pipe_input;

	result = NULL;
	if (!check_cmd_num(cmd_line))
	{
		print_err_msg();
		free_pipe_input(&pipe_input);
		return (NULL);
	}
	if (cmd_line->command_num == ECHO)
		result = echo(cmd_line, env, pipe_input);
	if (cmd_line->command_num == EXPORT)
		result = export(cmd_line, env, pipe_input);
	// else if (cmd_line->command_num == CD)
	// 	result = cd(cmd_line, env, pipe_input);
	if (cmd_line->pipe_flag)
	{
		free_pipe_input(&pipe_input);
		pipe_input = ft_strdup(result);
	}
	else
		free_pipe_input(&pipe_input);
	return (result);
}
