#include "command.h"

char	*pwd(t_cmd_line *cmd_line, char **pipe_flag)
{
	char	*dir;
	char	*tmp;

	if (!(tmp = getcwd(NULL, 0)))
		return (NULL);
	dir = ft_strjoin(tmp, "\n");
	write(1, dir, ft_strlen(dir));
	free(tmp);
	return (dir);
}
