#include "command.h"

bool		check_env_operator_cmd(t_cmd_line *cmd_line)
{
	if (cmd_line->command_num == CD)
		return (true);
	else if (cmd_line->command_num == EXPORT)
		return (true);
	else if (cmd_line->command_num == UNSET)
		return (true);
	else if (cmd_line->command_num == EXIT)
		return (true);
	return (false);
}

static bool	run_operator_cmd(t_cmd_line *cmd_line)
{
	if (cmd_line->command_num == CD)
		return (cd(cmd_line));
	else if (cmd_line->command_num == EXPORT)
		return (export(cmd_line));
	else if (cmd_line->command_num == EXIT)
		return (ft_exit(cmd_line));
	else if (cmd_line->command_num == UNSET)
		return (ft_unset(cmd_line));
	return (false);
}

bool		run_env_operator_cmd(t_cmd_line *cmd_line, \
									t_pipes *pipes, bool *pipe_flag)
{
	int		reset[2];
	bool	return_flag;

	return_flag = true;
	reset[0] = dup(0);
	reset[1] = dup(1);
	if (!set_pipe(cmd_line, *pipe_flag, pipes) || !run_operator_cmd(cmd_line))
	{
		close_redir_file(cmd_line);
		built_in_error();
		return_flag = false;
	}
	close_redir_file(cmd_line);
	if (*pipe_flag)
	{
		close(get_read_fd(pipes));
		pipes->old[READ] = -1;
	}
	dup2(reset[1], 1);
	dup2(reset[0], 0);
	set_pipe_flag(cmd_line, pipe_flag);
	return (return_flag);
}
