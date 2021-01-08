/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dokang <dokang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 17:19:22 by dokang            #+#    #+#             */
/*   Updated: 2021/01/07 17:19:24 by dokang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

bool		init_pipe(t_pipes *pipes)
{
	if (pipe(pipes->old) < 0 || pipe(pipes->new) < 0)
	{
		built_in_error();
		set_exit_status(EX_OSERR);
		return (false);
	}
	return (true);
}

void		swap_pipe(t_pipes *pipes)
{
	if (pipes->old[READ] == -1 && pipes->old[WRITE] == -1)
	{
		pipes->old[READ] = pipes->new[READ];
		pipes->old[WRITE] = pipes->new[WRITE];
		pipe(pipes->new);
	}
}

void		set_pipe_flag(t_cmd_line *cmd_line, bool *pipe_flag)
{
	if (cmd_line->pipe_flag)
		*pipe_flag = true;
	else
		*pipe_flag = false;
}

static bool	set_redir_fd(t_cmd_line *cmd_line, t_pipes *pipes, \
						t_list *redir_list, bool *has_redir)
{
	t_redir		*redir;

	*has_redir = true;
	redir = redir_list->content;
	redir->file_fd = find_file_fd(redir);
	if (redir->file_fd < 0)
	{
		set_exit_status(EX_NOINPUT);
		return (false);
	}
	if (cmd_line->param_err)
	{
		cmd_line->param_err = false;
		return (true);
	}
	if (redir->redir_flag == REDIR_IN)
	{
		dup2(redir->file_fd, 0);
		if (cmd_line->pipe_flag)
			dup2(get_write_fd(pipes), 1);
	}
	else
		dup2(redir->file_fd, 1);
	return (true);
}

bool		set_pipe(t_cmd_line *cmd_line, bool flag,
							t_pipes *pipes)
{
	t_list		*redir_list;
	bool		has_redir;

	if (flag)
		dup2(get_read_fd(pipes), 0);
	has_redir = false;
	redir_list = cmd_line->redir_param;
	while (redir_list)
	{
		if (!set_redir_fd(cmd_line, pipes, redir_list, &has_redir))
			return (false);
		redir_list = redir_list->next;
	}
	if (cmd_line->pipe_flag && !has_redir)
		dup2(get_write_fd(pipes), 1);
	return (true);
}
