#include "minishell.h"

static void	set_pipe_flag(t_cmd_line *cmd_line, bool *flag,
							int *pipe_fd, char *buf)
{
	if (*flag)
	{
		read(pipe_fd[0], buf, BUFFER_SIZE);
		*flag = 0;
	}
	if (cmd_line->pipe_flag 
		|| cmd_line->redir_flag == OUT_ENDLINE
		|| cmd_line->redir_flag == OUT_OVERRIDE)
	{
		dup2(pipe_fd[1], 1);
		*flag = 1;
	}
}

static void	run(t_cmd_line *cmd_line, t_list *env, int *pipe_fd)
{
	bool	flag;
	char	*buf;
	char	*errmsg;
	int		status;
	pid_t	pid;
	
	buf = ft_calloc(sizeof(char), BUFFER_SIZE);
	flag = false;
	pid = fork();
	if (pid > 0)
	{
		waitpid(pid, &status, 0);
		check_and_set_redir_out(cmd_line, env, buf, pipe_fd);
	}
	else if (pid == 0)
	{
		set_pipe_flag(cmd_line, &flag, pipe_fd, buf);
		check_and_set_redir_in(cmd_line, env, buf);
		run_command(cmd_line, env, buf);
		free(buf);
		exit(0);
	}
	free(buf);
}

void	minishell(char *line, t_list *env)
{
	t_cmd_line		*command_line;
	pid_t			pid;
	int				status;
	int 			pipe_fd[2];

	pipe(pipe_fd);
	g_err.err_number = 0;
	g_err.err_value = 0;
	// signal(SIGINT, child_exit);
	// signal(SIGQUIT, child_exit);
	if (!validate_line(line))
	{
		// printf("errnum = %d\n", g_err.err_number);
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
		run(command_line, env, pipe_fd);
		free_cmd_struct(command_line);
		free(command_line);
	}
}
