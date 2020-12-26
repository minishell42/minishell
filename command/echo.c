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

// pipe, redir flag가 있는 경우 리턴해줘야 한다.
bool	echo(t_cmd_line *cmd_line, t_list *env)
{
	char *ret;

	if (!(ret = ft_strdup(cmd_line->param)))
		return (false);
	apply_echo_option(cmd_line, &ret);
	if (write(1, ret, ft_strlen(ret)) < 0)
	{
		free(ret);
		return (false);
	}
	free(ret);
	return (true);
}
