#include "parsing.h"

static int		check_start_line(char *line, int i)
{
	if (!line || !(*line))
		return (0);
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (line[i] == ';' || line[i] == '|')
		return (set_syntax_err(line, i));
	return (1);
}

static int		check_validate_line(char *line, char *flag)
{
	int	i;

	i = 0;
	while (line[i])
	{
		while (line[i] && !is_delimitor(line[i]))
			i++;
		if (line[i] && !*flag)
		{
			*flag = line[i++];
			if (*flag == '>' && line[i] == '>')
				i++;
		}
		while (ft_isspace(line[i]))
			i++;
		if (*flag && is_delimitor(line[i]))
			return (set_syntax_err(line, i));
		if (line[i])
		{
			*flag = 0;
			i++;
		}
	}
	return (1);
}

int				validate_line(char *line)
{
	int		i;
	char	flag;
	bool	ret;

	i = 0;
	flag = 0;
	ret = true;
	if (!check_start_line(line, i))
		ret = false;
	else if (!check_validate_line(line + i, &flag))
		ret = false;
	else if (flag && flag != ';')
	{
		make_err_msg(SYNTAX_ERROR, 0, 0, get_err_msg(PARAM_IS_NEWLINE));
		ret = false;
	}
	if (!ret)
		built_in_error();
	return (ret);
}

void			set_special_param(t_cmd_line *cmd_line)
{
	t_list	*param_list;
	char	*param;
	char	*special_param;

	param_list = cmd_line->param;
	while (param_list)
	{
		param = param_list->content;
		if (are_equal(param, "$?"))
		{
			special_param = ft_itoa(g_exit_code);
			param_list->content = special_param;
			free(param);
		}
		param_list = param_list->next;
	}
}
