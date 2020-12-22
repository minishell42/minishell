#include "minishell.h"

static void	set_pipe_flag(t_cmd_line *cmd_line, t_list *env, bool flag,
							int *pipe_fd)
{
	// flag 확인 
	// flag에 맞는 fd 받아오기
	// flag에 맞는 fd dup하기
	// grep 1 < 456 | grep 13 => 1333

	if (flag)
	{
		printf("in ? \n");
		dup2(pipe_fd[0], 0);
		// 0 ---> pipe_fd[0]
		// 1 ---> pipe_fd[1]
		// grep 13 --> 1 --> pipe_fd[1] ---> pipe_fd[0] ---> 0 ---> grep // 무한 

		// 부모 프로세스
		// pipe()
		// fork()

		// 자식 프로세스
		// 부모꺼랑 똑같은 pipe()
		// dup2()
		// kill

	}
	printf("blcok test\n");
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
				dup2(pipe_fd[1], 1);
				// read(pipe_fd[0], buf, BUFFER_SIZE);
				// printf("pipe buffer = %s\n", buf);
				// grep 1 < 456 | grep 13
				// < 456 == dup2(file_fd, 0) // 0 ---> file_fd
				// grep 1 --> pipe_fd[1] // 1 ---> pipe_fd[1]
			}
		}
		else
			dup2(file_fd, 1);
	}
	else if (cmd_line->pipe_flag)
	{
		dup2(pipe_fd[1], 1);

	}
}

static void	run(t_cmd_line *cmd_line, t_list *env, int *pipe_fd, bool *pipe_flag)
{
	char	*buf;
	char	*errmsg;
	int		status;
	pid_t	pid;
	
	printf("start run\n");
	buf = ft_calloc(sizeof(char), BUFFER_SIZE);
	pid = fork();
	if (pid > 0)
	{
		waitpid(pid, &status, 0);
		printf("end child\n");
		// out과 pipe가 둘 다 있을 경우 후처리?
	}
	else if (pid == 0)
	{
		set_pipe_flag(cmd_line, env, *pipe_flag, pipe_fd);
		if (!run_command(cmd_line, env, buf))
			built_in_error();
		free(buf);
		exit(0);
	}
	if (cmd_line->pipe_flag)
		*pipe_flag = true;
	else
		*pipe_flag = false;
	printf("end run\n");
	free(buf);
}

void	minishell(char *line, t_list *env)
{
	t_cmd_line		*command_line;
	pid_t			pid;
	int				status;
	int 			pipe_fd[2];
	bool			pipe_flag;

	pipe(pipe_fd);
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
		run(command_line, env, pipe_fd, &pipe_flag);
		close(pipe_fd[1]);
		free_cmd_struct(command_line);
		free(command_line);
	}
}
