#include "ft_error.h"

// =====================  before  =========================
// void	built_in_error()
// {
// 	char	*errmsg;

// 	errmsg = strerror(errno);
// 	write(1, errmsg, ft_strlen(errmsg));
// 	write(1, "\n", 1);
// 	exit(EXIT_FAILURE);
// }

// =====================  after  =========================
// add print_err_msg in built_in_error
void	built_in_error()
{
	char	*errmsg;

	if (g_err.err_number)
		print_err_msg();
	else
	{
		errmsg = strerror(errno);
		write(1, errmsg, ft_strlen(errmsg));
		write(1, "\n", 1);
		exit(EXIT_FAILURE);
	}
}
