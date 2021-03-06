/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_handler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dokang <dokang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 17:19:15 by dokang            #+#    #+#             */
/*   Updated: 2021/01/07 17:19:17 by dokang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

void		close_write_fd(t_pipes *pipes)
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

void		close_pipe_fd(t_pipes *pipes)
{
	if (pipes->old[WRITE] != -1)
		close(pipes->old[WRITE]);
	if (pipes->old[READ] != -1)
		close(pipes->old[READ]);
	if (pipes->new[WRITE] != -1)
		close(pipes->new[WRITE]);
	if (pipes->new[READ] != -1)
		close(pipes->new[READ]);
}

int			get_write_fd(t_pipes *pipes)
{
	if (pipes->old[WRITE] == -1)
		return (pipes->new[WRITE]);
	return (pipes->old[WRITE]);
}

int			get_read_fd(t_pipes *pipes)
{
	if (pipes->old[READ] == -1)
		return (pipes->new[READ]);
	return (pipes->old[READ]);
}

int			find_file_fd(t_redir *redir)
{
	char	*file_name;
	int		fd;

	fd = -1;
	file_name = change_to_absolute_path(redir->redir_param);
	if (!file_name)
		file_name = ft_strdup(redir->redir_param);
	if (redir->redir_flag == OUT_ENDLINE)
		fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (redir->redir_flag == OUT_OVERRIDE)
		fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (redir->redir_flag == REDIR_IN)
		fd = open(file_name, O_RDONLY);
	free(file_name);
	return (fd);
}
