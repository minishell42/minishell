#include "command.h"

static bool	redirection_out(t_cmd_line *cmd_line, t_list *env, char *res)
{
	char	*file_name;
	int		fd;
	t_list	*redir_param;
	int		len;

	len = 0;
	if (!cmd_line->redir_flag)
		return (true);
	redir_param = cmd_line->redir_param;
	file_name = change_to_absolute_path((char *)redir_param->content, env);
	if (!file_name)
		file_name = cmd_line->redir_param->content;
	if (cmd_line->redir_flag == OUT_ENDLINE)
		fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (cmd_line->redir_flag == OUT_OVERRIDE)
		fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC , 0644);
	if (fd < 0)
		return (false);
	if (res)
		len = ft_strlen(res);
	write(fd, res, len);
	close(fd);
	return (true);
}

void		check_and_set_redir_out(t_cmd_line *cmd_line, t_list *env, char *buf, int *pipe_fd)
{
	if (cmd_line->redir_flag && cmd_line->redir_flag != REDIR_IN)
	{
		read(pipe_fd[0], buf, BUFFER_SIZE);
		if(!redirection_out(cmd_line, env, buf))
		{
			free(buf);
			built_in_error();
		}
		if (cmd_line->pipe_flag)
			write(pipe_fd[1], "", 1);
	}
}

static bool	redirection_in(t_cmd_line *cmd_line, t_list *env, char *buf)
{
	char	*file_name;
	int		fd;
	t_list	*redir_param;
	int		len;

	len = 0;
	if (!cmd_line->redir_flag)
		return (true);
	redir_param = cmd_line->redir_param;
	file_name = change_to_absolute_path((char *)redir_param->content, env);
	if (!file_name)
		file_name = cmd_line->redir_param->content;
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return (false);
	read(fd, buf, BUFFER_SIZE);
	return (true);
}

void		check_and_set_redir_in(t_cmd_line *cmd_line, t_list *env, char *buf)
{
	if (cmd_line->redir_flag == REDIR_IN)
	{
		if (!redirection_in(cmd_line, env, buf))
		{
			free(buf);
			built_in_error();
		}
	}
}
