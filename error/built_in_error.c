#include "ft_error.h"

void	built_in_error()
{
	char	*errmsg;

	if (g_err.err_number)
		print_err_msg();
	else
	{
		errmsg = strerror(errno);
		write(2, errmsg, ft_strlen(errmsg));
		write(2, "\n", 1);
		exit(EXIT_FAILURE);
	}
}

