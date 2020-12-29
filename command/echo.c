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
bool	echo(t_cmd_line *cmd_line)
{
	char	*ret;
	char	*param;

	param = convert_to_valid_value(cmd_line->param,
									ft_strlen(cmd_line->param));
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
