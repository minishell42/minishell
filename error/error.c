#include "ft_error.h"

void	message_and_exit(char *message, bool built_in_error)
{
	char	*error_msg;

	error_msg = ft_strjoin("Error\n", message);
	if (built_in_error)
		perror(error_msg);
	else
		write(2, error_msg, strlen(error_msg));
	exit(1);
}

char	*get_err_msg(int err_number)
{
	if (err_number == QUOT_IS_NOT_PAIR)
		return ("quotation mark is not pair\n");
	else if (err_number == INVALID_COMMAND)
		return ("invalid command entered\n");
	else if (err_number == TOO_MANY_REDIR)
		return ("too many redirects exist\n");
	else if (err_number == SYNTAX_ERROR)
		return ("syntax error near unexpected token\n");
	else if (err_number == PARAM_IS_NEWLINE)
		return ("syntax error near unexpected token `newline'\n");
	else if (err_number == INVALID_EXPORT_PARAM)
		return ("is invalid export param\n");
	else if (err_number == TOO_MANY_REDIR_PARAM)
		return ("too many arguments\n");
	else if (err_number == NO_FILE_OR_DIRECTORY)
		return ("No such file or directory\n");
	else if (err_number == NO_OLDPWD)
		return ("OLDPWD not set\n");
	else if (err_number == NO_HOME)
		return ("HOME not set\n");
	return (NULL);
}

void	free_err_info(void *content)
{
	t_error *err_info;

	err_info = content;
	if (err_info->err_value)
		free(err_info->err_value);
	free(err_info);
}

void	print_err_msg(void)
{
	char	*err_msg;
	char	*msg;
	t_error	*err_info;
	t_list	*curr;

	curr = g_err;
	while (curr)
	{
		err_info = curr->content;
		err_msg = err_info->err_value;
		write(2, err_msg, ft_strlen(err_msg));
		curr = curr->next;
	}
	ft_lstclear(&g_err, free_err_info);
	g_err = 0;
}

void	set_quot_err(char quot_flag)
{
	char	*err_value;

	if (!(err_value = ft_calloc(sizeof(char), 2)))
		return ;
	err_value[0] = quot_flag;
	make_err_msg(0, err_value, get_err_msg(QUOT_IS_NOT_PAIR));
	free(err_value);
}

int		set_syntax_err(char *line, int i)
{
	char	*err_value;
	err_value = ft_calloc(sizeof(char), 3);
	err_value[0] = line[i];
	if (line[i] == line[i - 1] || line[i] == line[i + 1])
		err_value[1] = line[i];
	make_err_msg(0, err_value, get_err_msg(SYNTAX_ERROR));
	free(err_value);
	return (0);
}

void	err(char *str)
{
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
}