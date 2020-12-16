#include "command.h"

char	*pwd(t_cmd_line *cmd_line, char **pipe_flag)
{
	char	*dir;
	char	*tmp;

	if (!(tmp = getcwd(NULL, 0)))
		return (NULL);
	dir = ft_strjoin(tmp, "\n");
	if (!cmd_line->redir_flag && !cmd_line->pipe_flag)
		write(1, dir, ft_strlen(dir));
	if (cmd_line->pipe_flag)
		if (*pipe_flag)
		{
			free(*pipe_flag);
			*pipe_flag = NULL;
		}
	free(tmp);
	return (dir);
}
