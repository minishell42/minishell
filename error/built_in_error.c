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

void	make_err_msg(int error_number, char *cmd, char *value, char *msg)
{
	char	*tmp;
	char	*str;
	char	*cmd_tmp;
	char	*val_tmp;
	char	*result;

	tmp = ft_strdup(msg);
	cmd_tmp = ft_strjoin(cmd, ": ");
	val_tmp = ft_strjoin(value, ": ");
	str = ft_strjoin(cmd_tmp, val_tmp);
	result = ft_strjoin(str, tmp);
	free(tmp);
	free(cmd_tmp);
	free(val_tmp);
	free(str);
	parsing_err_value(error_number, result);
	free(result);
}
