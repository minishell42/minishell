#include "command.h"

int			find_file_fd(t_cmd_line *cmd_line, t_list *env)
{
	char	*file_name;
	int		fd;
	t_list	*redir_param;

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
	return (fd);
}
