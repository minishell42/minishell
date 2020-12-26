#include "command.h"

int			find_file_fd(t_redir *redir, t_list *env)
{
	char	*file_name;
	int		fd;

	file_name = change_to_absolute_path(redir->redir_param, env);
	if (!file_name)
		file_name = redir->redir_param;
	if (redir->redir_flag == OUT_ENDLINE)
		fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (redir->redir_flag == OUT_OVERRIDE)
		fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC , 0644);
	else if (redir->redir_flag == REDIR_IN)
		fd = open(file_name, O_RDONLY);
	return (fd);
}
