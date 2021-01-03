#include "minishell.h"

static bool	run(t_cmd_line *cmd_line, t_pipes *pipes, bool *pipe_flag)
{
	if (check_env_operator_cmd(cmd_line))
	{
		if (!run_env_operator_cmd(cmd_line, pipes, pipe_flag))
			return (false);
	}
	else
		return (run_normal_cmd(cmd_line, pipes, pipe_flag));
	return (true);
}

static bool	set_condition_after_run(t_cmd_line *cmd_line, t_pipes *pipes)
{
	close_write_fd(pipes);
	swap_pipe(pipes);
	free_cmd_struct(cmd_line);
	set_exit_status(EXIT_SUCCESS);
}

void		minishell(char *line)
{
	t_cmd_line		*command_line;
	pid_t			pid;
	int				status;
	bool			pipe_flag;
	t_pipes			pipes;

	if (!init_pipe(&pipes) || !validate_line(line))
		return ;
	pipe_flag = false;
	while (line && *line)
	{
		if (!(command_line = get_command_line(&line)))
		{
			built_in_error();
			set_exit_status(SYNTAX_ERROR);
			return ;
		}
		if (!run(command_line, &pipes, &pipe_flag))
		{
			free_cmd_struct(command_line);
			return ;
		}
		set_condition_after_run(command_line, &pipes);
	}
}
