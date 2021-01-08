/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dokang <dokang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 17:16:21 by dokang            #+#    #+#             */
/*   Updated: 2021/01/07 17:16:22 by dokang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static void	set_condition_after_run(t_cmd_line *cmd_line, t_pipes *pipes)
{
	close_write_fd(pipes);
	swap_pipe(pipes);
	free_cmd_struct(cmd_line);
}

void		minishell(char *line)
{
	t_cmd_line		*command_line;
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
			close_pipe_fd(&pipes);
			return ;
		}
		if (!run(command_line, &pipes, &pipe_flag))
		{
			set_condition_after_run(command_line, &pipes);
			continue ;
		}
		set_condition_after_run(command_line, &pipes);
		set_exit_status(EXIT_SUCCESS);
	}
	close_pipe_fd(&pipes);
}
