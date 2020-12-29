#include "parsing.h"

char		*convert_to_valid_value(char *start, int len)
{
	char	*result;
	char	*str;
	char	*tmp;

	str = ft_calloc(sizeof(char), len + 1);
	ft_strlcpy(str, start, len + 1);
	tmp = set_multi_env(str);
	free(str);
	remove_quotation(tmp);
	result = ft_strtrim(tmp, " ");
	free(tmp);
	return (result);
}

int			set_param(t_cmd_line *command_line, char *start)
{
	char	*param;
	int		param_len;
	int		i;

	i = 0;
	if (!check_character_in_line(start, &i, is_separator))
		return (-1);
	if (start[i] == '|')
		command_line->pipe_flag = true;
	command_line->param = ft_substr(start, 0, i);
	if (start[i])
		i++;
	return (i);
}
