#include "ft_error.h"

void	built_in_error()
{
	char	*errmsg;

	errmsg = strerror(errno);
	write(1, errmsg, ft_strlen(errmsg));
	write(1, "\n", 1);
	exit(EXIT_FAILURE);
}

