/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dokang <dokang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 17:05:18 by dokang            #+#    #+#             */
/*   Updated: 2021/01/07 17:05:21 by dokang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

static char	**make_exec_args(t_cmd_line *cmd_line)
{
	t_list	*args_list;
	char	**args;
	char	*arg;

	arg = ft_strdup(cmd_line->command);
	args_list = cmd_line->param;
	ft_lstadd_front(&args_list, ft_lstnew(arg));
	if (!args_list)
		return (NULL);
	args = convert_to_array_env_list(args_list);
	free(args_list);
	return (args);
}

static bool	run_binary(t_cmd_line *cmd_line, char *file_path)
{
	char	**envp;
	char	**args;

	envp = convert_to_array_env_list(g_env);
	args = make_exec_args(cmd_line);
	if (execve(file_path, args, envp) == -1)
	{
		free_str_array(envp);
		free_str_array(args);
		free(file_path);
		return (false);
	}
	return (true);
}

bool		run_command(t_cmd_line *cmd_line)
{
	char		*file_path;

	if (cmd_line->command_num == ECHO)
		return (echo(cmd_line));
	else if (cmd_line->command_num == PWD)
		return (pwd());
	else if (cmd_line->command_num == ENV)
		return (ft_env(cmd_line));
	else if ((file_path = search_file(cmd_line, cmd_line->command)))
		return (run_binary(cmd_line, file_path));
	else if (!check_cmd_num(cmd_line))
		return (false);
	return (false);
}

static bool	set_parents_condition(t_cmd_line *cmd_line, \
				t_pipes *pipes, bool *pipe_flag, int status)
{
	set_exit_status(status);
	if (*pipe_flag)
	{
		close(get_read_fd(pipes));
		pipes->old[READ] = -1;
	}
	set_pipe_flag(cmd_line, pipe_flag);
	if (status)
		return (false);
	return (true);
}

bool		run_normal_cmd(t_cmd_line *cmd_line, \
							t_pipes *pipes, bool *pipe_flag)
{
	pid_t	pid;
	int		status;

	status = 0;
	signal_ignore();
	pid = fork();
	if (pid > 0)
		waitpid(pid, &status, 0);
	else if (pid == 0)
	{
		init_child_signal();
		if ((!set_pipe(cmd_line, *pipe_flag, pipes)) \
				|| (!run_command(cmd_line)))
		{
			close_redir_file(cmd_line);
			built_in_error();
			exit(g_exit_code);
		}
		close_redir_file(cmd_line);
		exit(0);
	}
	return (set_parents_condition(cmd_line, pipes, pipe_flag, status));
}
