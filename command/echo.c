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
char	*echo(t_cmd_line *cmd_line, t_list *env, char *pipe_input)
{
	char *ret;

	ret = ft_strdup(cmd_line->param);
	apply_echo_option(cmd_line, &ret);
	if (cmd_line->redir_flag == OUT_ENDLINE
		|| cmd_line->redir_flag == OUT_OVERRIDE
		|| cmd_line->pipe_flag)
		return ret;
	write(1, ret, ft_strlen(ret));
	free(ret);
	return (NULL);
}
