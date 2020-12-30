#include "ft_error.h"

void	built_in_error()
{
	char	*errmsg;

	if (g_err)
		print_err_msg();
	else
	{
		errmsg = strerror(errno);
		write(2, errmsg, ft_strlen(errmsg));
		write(2, "\n", 1);
	}
}

static void	parsing_err_value(char *error_point)
{
	t_error *err_info;

	err_info = ft_calloc(sizeof(t_error), 1);
	if (error_point)
		err_info->err_value = ft_strdup(error_point);
	if (g_err)
		ft_lstadd_back(&g_err, ft_lstnew(err_info));
	else
		g_err = ft_lstnew(err_info);
}

void		make_err_msg(char *cmd, char *value, char *msg)
{
	char	*str;
	char	*cmd_tmp;
	char	*val_tmp;
	char	*result;

	val_tmp = NULL;
	cmd_tmp = NULL;
	if (cmd)
		cmd_tmp = ft_strjoin(cmd, " : ");
	if (value)
		val_tmp = ft_strjoin(value, " : ");
	str = ft_strjoin(cmd_tmp, val_tmp);
	result = ft_strjoin(str, msg);
	if (val_tmp)
		free(val_tmp);
	if (cmd_tmp)
		free(cmd_tmp);
	free(str);
	parsing_err_value(result);
	free(result);
}
