#include "command.h"

bool	redirection(t_cmd_line *cmd_line, t_list *env, char *res)
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
	else if (cmd_line->redir_flag == REDIR_IN)
		fd = open(file_name, O_RDONLY);
	if (fd < 0)
	{
		perror("redirection\n");
		return (false);
	}
	if (res)
		len = ft_strlen(res);
	write(fd, res, len);
	close(fd);
	return (true);
}