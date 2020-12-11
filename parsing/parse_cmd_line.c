#include "parsing.h"

int			get_command_num(char *command)
{
    if (are_equal(command, "echo"))
	{
		return (ECHO);
	}
	return (0);
}

void		change_param_value(t_cmd_line *cmd_line, t_list *env)
{
	if (cmd_line->redir_flag)
		set_redirection_param(cmd_line, env);
	else
	{
		cmd_line->param = set_multi_env(cmd_line->param, env); // 메모리 누수 가능성 : parameter : cmd_line
		remove_quotation(cmd_line->param);
		cmd_line->param = ft_strtrim(cmd_line->param, " "); // 메모리 누수 가능성
	}
}

char		*convert_to_valid_value(char *start, int len, t_list *env)
{
	char	*result;
	char	*tmp;

	tmp = ft_calloc(sizeof(char), len + 1);
	ft_strlcpy(tmp, start, len + 1);
	tmp = set_multi_env(tmp, env); // 메모리 누수 조심
	remove_quotation(tmp);
	result = ft_strtrim(tmp, " ");
	free(tmp);
	return (result);
}

int			set_param(t_cmd_line *command_line, char *start, t_list *env)
{
	char	*param;
	int		param_len;
	char	flag;
	int		i;

	i = 0;
	flag = 0;
	check_chacter_in_line(start, &i, &flag, is_separator);
	if (start[i] == '|')
		command_line->pipe_flag = true;
	command_line->param = convert_to_valid_value(start, i, env);
	return (i + 1);
}

int			parse_command(t_cmd_line *cmd_line, char *start, int len, t_list *env)
{
	char	*value;

	value = convert_to_valid_value(start, len, env);
	if (!cmd_line->command)
	{
		cmd_line->command = value;
		cmd_line->command_num = get_command_num(cmd_line->command);
		if (!cmd_line->command_num)
			return (INVALID_COMMAND);
		// !cmd_line->command_num 에러처리
		return (true);
	}
	else if (cmd_line->command_num == ECHO && are_equal(value, "-n"))
	{
		if (!cmd_line->option)
			cmd_line->option = value;
		else
			free(value);
		return (true);
	}
	free(value);
	return (false);
}
