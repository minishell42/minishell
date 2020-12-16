#include "ft_error.h"

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

void	print_err_msg(void)
{
	int 	err_number;
	char	*err_msg;
	char	*msg;

	err_number = g_err.err_number;
	if (err_number == ALLOC_ERROR)
		err_msg = "malloc error\n";
	else if (err_number == QUOT_IS_NOT_PAIR)
		err_msg = " quotation mark is not pair\n";
	else if (err_number == INVALID_COMMAND)
		err_msg = " invalid command entered\n";
	else if (err_number == TOO_MANY_REDIR)
		err_msg = " too many redirects exist\n";
	if (!(msg = ft_strjoin(g_err.err_value, err_msg)))
		msg = err_msg;
	write(1, msg, ft_strlen(msg));
	if (g_err.err_value)
	{
		free(g_err.err_value);
		free(msg);
	}
	g_err.err_value = 0;
	g_err.err_number = 0;
}

bool	parsing_err_value(int error_number, char *error_point)
{
	g_err.err_number = error_number;
	g_err.err_value = ft_strdup(error_point);
	return (false);
}

void	set_quot_err(char quot_flag)
{
	if (!(g_err.err_value = ft_calloc(sizeof(char), 2)))
		g_err.err_number = ALLOC_ERROR;
	else
	{
		g_err.err_value[0] = quot_flag;
		g_err.err_number = QUOT_IS_NOT_PAIR;
	}
}