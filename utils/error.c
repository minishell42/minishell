#include "utils.h"

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