#include "command.h"

static char		*make_arg(char *param, int start, int len)
{
	char	*tmp;
	char	*arg;

	tmp = ft_substr(param, start, len);
	if (!tmp)
		return (NULL);
	arg = convert_to_valid_value(tmp, ft_strlen(tmp));
	free(tmp);
	if (!arg)
		return (NULL);
	return (arg);
}

static t_list	*make_args_list(t_cmd_line *cmd_line)
{
	t_list	*args_list;
	int		start;
	int		index;
	char	*param;
	char	*arg;

	index = 0;
	start = index;
	param = cmd_line->param;
	args_list = NULL;
	while (param[index] && check_character_in_line(param, &index, ft_isspace))
	{
		while (ft_isspace(param[index]))
			index++;
		arg = make_arg(param, start, index - start);
		if (!arg)
			return (NULL);
		ft_lstadd_back(&args_list, ft_lstnew(arg));
		if (param[index] && param[index] == ' ')
			index++;
		start = index;
	}
	arg = ft_strdup(cmd_line->command);
	ft_lstadd_front(&args_list, ft_lstnew(arg));
	return (args_list);
}

static char	**make_exec_args(t_cmd_line *cmd_line)
{
	t_list	*args_list;
	char	**args;

	args_list = make_args_list(cmd_line);
	if (!args_list)
		return (NULL);
	args = convert_to_array_env_list(args_list);
	return (args);
}

static bool	run_binary(t_cmd_line *cmd_line)
{
	char	*root;
	char 	*file_path;
	char	**envp;
	char	**args;

	envp = convert_to_array_env_list(g_env);
	args = make_exec_args(cmd_line);
	if (execve(file_path, args, envp) == -1)
		return (false);
	return (true);
}

bool		run_command(t_cmd_line *cmd_line)
{
	char		*file_path;

	if (cmd_line->command_num == ECHO)
		return (echo(cmd_line));
	else if (cmd_line->command_num == PWD)
		return (pwd(cmd_line));
	else if (cmd_line->command_num == CD)
		return (cd(cmd_line));
	// else if (cmd_line->command_num == PWD)
	// 	pwd(cmd_line);
	// else if (cmd_line->command_num == EXPORT)
	// 	export(cmd_line);
	// else if (cmd_line->command_num == EXIT)
	// 	ft_exit(cmd_line);
	else if((file_path = search_file(cmd_line->command)))
		return (run_binary(cmd_line));
	else if (!check_cmd_num(cmd_line))
		return (false);
	return (true);
}
