#include "minishell.h"

# define READ 0
# define WRITE 1

int		get_write_fd(t_pipes *pipes)
{
	if (pipes->old[WRITE] == -1)
		return (pipes->new[WRITE]);
	return (pipes->old[WRITE]);
}

int		get_read_fd(t_pipes *pipes)
{
	if (pipes->old[READ] == -1)
		return (pipes->new[READ]);
	return (pipes->old[READ]);
}

static bool	set_pipe(t_cmd_line *cmd_line, bool flag,
							t_pipes *pipes)
{
	t_list		*redir_list;
	t_redir		*redir;
	int			file_fd;
	bool		has_redir;

	if (flag)
		dup2(get_read_fd(pipes), 0);
	has_redir = false;
	redir_list = cmd_line->redir_param;
	while (redir_list)
	{
		has_redir = true;
		redir = redir_list->content;
		file_fd = find_file_fd(redir);
		if (file_fd < 0)
			return (false);
		if (redir->redir_flag == REDIR_IN)
		{
			dup2(file_fd, 0);
			if (cmd_line->pipe_flag)
				dup2(get_write_fd(pipes), 1);
		}
		else
			dup2(file_fd, 1);
		redir_list = redir_list->next;
	}
	if (cmd_line->pipe_flag && !has_redir)
		dup2(get_write_fd(pipes), 1);
	return (true);
}

static bool check_env_operator_cmd(t_cmd_line *cmd_line)
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

void		set_pipe_flag(t_cmd_line *cmd_line, bool *pipe_flag)
{
	if (cmd_line->pipe_flag)
		*pipe_flag = true;
	else
		*pipe_flag = false;
}

static bool run_env_operator_cmd(t_cmd_line *cmd_line,
									t_pipes *pipes, bool *pipe_flag)
{
	int		reset[2];
	bool	return_flag;

	return_flag = true;
	reset[0] = dup(0);
	reset[1] = dup(1);
	if (!set_pipe(cmd_line, *pipe_flag, pipes) || !run_operator_cmd(cmd_line))
	{
		built_in_error();
		return_flag = false;
	}
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

void		run_normal_cmd(t_cmd_line *cmd_line, t_pipes *pipes, bool *pipe_flag)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid > 0)
	{
		waitpid(pid, &status, 0);
		if (*pipe_flag)
		{
			close(get_read_fd(pipes));
			pipes->old[READ] = -1;
		}
	}
	else if (pid == 0)
	{
		init_child_signal();
		if ((!set_pipe(cmd_line, *pipe_flag, pipes)) || (!run_command(cmd_line)))
			built_in_error();
		exit(0);
	}
	set_pipe_flag(cmd_line, pipe_flag);
}

static bool	run(t_cmd_line *cmd_line, t_pipes *pipes, bool *pipe_flag)
{	
	if (check_env_operator_cmd(cmd_line))
	{
		if (!run_env_operator_cmd(cmd_line, pipes, pipe_flag))
			return (false);
	}
	else
		run_normal_cmd(cmd_line, pipes, pipe_flag);
	return (true);
}

void	init_pipe(t_pipes *pipes)
{
	pipe(pipes->old);
	pipe(pipes->new);
}

void	close_write_fd(t_pipes *pipes)
{
	if (pipes->old[WRITE] != -1)
	{
		close(pipes->old[WRITE]);
		pipes->old[WRITE] = -1;
	}
	else
	{
		close(pipes->new[WRITE]);
		pipes->new[WRITE] = -1;
	}
}

void	swap_pipe(t_pipes *pipes)
{
	if (pipes->old[READ] == -1 && pipes->old[WRITE] == -1)
	{
		pipes->old[READ] = pipes->new[READ];
		pipes->old[WRITE] = pipes->new[WRITE];
		pipe(pipes->new);
	}
}

void	minishell(char *line)
{
	t_cmd_line		*command_line;
	pid_t			pid;
	int				status;
	bool			pipe_flag;
	t_pipes 		pipes;

	init_pipe(&pipes);
	pipe_flag = false;
	if (!validate_line(line))
	{
		built_in_error();
		return ;
	}
	while (line && *line)
	{
		if (!(command_line = get_command_line(&line)))
		{
			built_in_error();
			return ;
		}
		if (!run(command_line, &pipes, &pipe_flag))
		{
			free_cmd_struct(command_line);
			return ;
		}
		close_write_fd(&pipes);
		swap_pipe(&pipes);
		free_cmd_struct(command_line);
	}
}
