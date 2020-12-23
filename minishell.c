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

static void	set_pipe_flag(t_cmd_line *cmd_line, t_list *env, bool flag,
							t_pipes *pipes)
{
	if (flag)
		dup2(get_read_fd(pipes), 0);
	if (cmd_line->redir_flag)
	{
		int file_fd = find_file_fd(cmd_line, env);
		if (file_fd < 0)
			built_in_error();
		if (cmd_line->redir_flag == REDIR_IN)
		{
			dup2(file_fd, 0);
			if (cmd_line->pipe_flag)
			{
				dup2(get_write_fd(pipes), 1);
			}
		}
		else
			dup2(file_fd, 1);
	}
	else if (cmd_line->pipe_flag)
	{
		dup2(get_write_fd(pipes), 1);

	}
}

static void	run(t_cmd_line *cmd_line, t_list *env, t_pipes *pipes, bool *pipe_flag)
{
	char	*buf;
	char	*errmsg;
	int		status;
	pid_t	pid;
	
	buf = ft_calloc(sizeof(char), BUFFER_SIZE);
	pid = fork();
	if (pid > 0)
	{
		waitpid(pid, &status, 0);
		if (*pipe_flag)
		{
			close(get_read_fd(pipes));
			pipes->old[READ] = -1;
		}
		// out과 pipe가 둘 다 있을 경우 후처리?
	}
	else if (pid == 0)
	{
		set_pipe_flag(cmd_line, env, *pipe_flag, pipes);
		if (!run_command(cmd_line, env, buf))
			built_in_error();
		free(buf);
		exit(0);
	}
	if (cmd_line->pipe_flag)
		*pipe_flag = true;
	else
		*pipe_flag = false;
	free(buf);
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


// void	printf_pipes(t_pipes *pipes)
// {
// 	printf("old read = %d\n old write = %d\n new read = %d\n new write = %d\n",
// 			pipes->old[READ], pipes->old[WRITE], pipes->new[READ], pipes->new[WRITE]);
// }

void	minishell(char *line, t_list *env)
{
	t_cmd_line		*command_line;
	pid_t			pid;
	int				status;
	bool			pipe_flag;
	t_pipes 		pipes;

	init_pipe(&pipes);
	g_err.err_number = 0;
	g_err.err_value = 0;
	pipe_flag = false;
	// signal(SIGINT, child_exit);
	// signal(SIGQUIT, child_exit);
	if (!validate_line(line))
	{
		if (g_err.err_number)
			print_err_msg();
		return ;
	}
	while (line && *line)
	{
		if (!(command_line = get_command_line(&line, env)))
		{
			// 따옴표 에러
			if (g_err.err_number)
				print_err_msg();
			return ;
		}
		run(command_line, env, &pipes, &pipe_flag);
		close_write_fd(&pipes);
		swap_pipe(&pipes);
		free_cmd_struct(command_line);
		free(command_line);
	}
}
