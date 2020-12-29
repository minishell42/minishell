#include "parsing.h"

void	apply_echo_option(t_cmd_line *cmd_line, char **ret)
{
	char *tmp;

	if (!cmd_line->option)
	{
		tmp = *ret;
		*ret = (ft_strjoin(*ret, "\n"));
		free(tmp);
	}
}

char	*make_param_str(t_cmd_line *cmd_line)
{
	t_list	*param_list;
	char	*param;
	char	*tmp;
	char	*result;

	param_list = cmd_line->param;
	result = ft_calloc(sizeof(char), 1);
	//param을 다 살펴본다.
	while (param_list)
	{
		param = (char *)param_list->content;
		tmp = result;
		result = ft_strjoin(result, param);
		free(tmp);
		param_list = param_list->next;
	}
	return (result);
}

// pipe, redir flag가 있는 경우 리턴해줘야 한다.
bool	echo(t_cmd_line *cmd_line)
{
	char	*ret;
	char	*param;

	param = make_param_str(cmd_line);
	if (!(param))
		return (false);
	apply_echo_option(cmd_line, &param);
	if (write(1, param, ft_strlen(param)) < 0)
	{
		free(param);
		return (false);
	}
	free(param);
	return (true);
}
