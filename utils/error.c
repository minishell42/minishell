#include "../include/error.h"

void	message_and_exit(char *message, bool built_in_error)
{
	char	*error_msg;

	error_msg = ft_strjoin("Error\n", message);
	if (built_in_error)
		perror(error_msg);
	else
		write(1, error_msg, strlen(error_msg));
	exit(1);
}

void	print_err_msg(char error_flag)
{
	if (error_flag == ALLOC_ERROR)
		write(1, "malloc error\n", 14);
	else if (error_flag == QUOT_IS_NOT_PAIR)
		write(1, "quotation mark is not pair\n", 28);
	else if (error_flag == INVALID_COMMAND)
		write(1, "invalid command\n", 17);
}

bool	parsing_err_value(int error_number, char *error_point)
{
	g_err.err_number = error_number;
	g_err.err_value = error_point;
	return (false);
}