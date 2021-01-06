#include "command.h"

bool	pwd(void)
{
	char	*dir;
	char	*tmp;

	if (!(tmp = getcwd(NULL, 0)))
		return (false);
	dir = ft_strjoin(tmp, "\n");
	free(tmp);
	if (!(write(1, dir, ft_strlen(dir))))
		return (false);
	free(dir);
	return (true);
}
