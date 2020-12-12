#include "parsing.h"

bool	change_param_value(t_cmd_line *cmd_line, t_list *env)
{
	char	*tmp;
	if (cmd_line->redir_flag)
	{
		if (!set_redirection_param(cmd_line, env))
			return (false);
	}
	else
	{
		tmp = cmd_line->param;
		cmd_line->param = set_multi_env(tmp, env);
		free(tmp);
		remove_quotation(cmd_line->param);
		tmp = cmd_line->param;
		cmd_line->param = ft_strtrim(tmp, " ");
		free(tmp);
	}
	return (true);
}

char		*convert_to_valid_value(char *start, int len, t_list *env)
{
	char	*result;
	char	*str;
	char	*tmp;

	str = ft_calloc(sizeof(char), len + 1);
	ft_strlcpy(str, start, len + 1);
	tmp = set_multi_env(str, env);
	free(str);
	remove_quotation(tmp);
	result = ft_strtrim(tmp, " ");
	free(tmp);
	return (result);
}

int			set_param(t_cmd_line *command_line, char *start, t_list *env)
{
	char	*param;
	int		param_len;
	int		i;

	i = 0;
	if (!check_character_in_line(start, &i, is_separator))
		return (-1);
	if (start[i] == '|')
		command_line->pipe_flag = true;
	command_line->param = convert_to_valid_value(start, i, env);
	return (i + 1);
}
