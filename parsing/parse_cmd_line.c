#include "parsing.h"

int			get_command_num(char *command)
{
    if (are_equal(command, "echo"))
	{
		return (ECHO);
	}
	// exit?
	return (0);
}

void		set_param(t_cmd_line *command_line, char *start)
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
	param_len = i + 1;
	param = ft_calloc(sizeof(char), param_len);
	ft_strlcpy(param, start, param_len);
	command_line->param = ft_strtrim(param, " ");
	free(param);
}

bool		parse_cmd_line(t_cmd_line *cmd_line, char *start, int len, t_list *env)
{
	char	*value;
	char	*env_value;

	// start = 한줄 len -> value
	// value = $EC$HO
	value = ft_calloc(sizeof(char), len + 1);
	ft_strlcpy(value, start, len + 1);
	// set_env(&value, env);
	value = set_multi_env(value, env);
	remove_quotation(value);
	// ft_function for check in env valuable name
	// if ((env_value = is_env(value, env)))
	// {
	// 	free(value);
	// 	value = env_value;
	// }
	if (!cmd_line->command)
	{
		cmd_line->command = value;
		cmd_line->command_num = get_command_num(cmd_line->command);
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
