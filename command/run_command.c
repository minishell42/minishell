#include "command.h"

static char	**make_exec_args(t_cmd_line *cmd_line)
{
	t_list	*args_list;
	char	**args;
	char	*arg;

	arg = ft_strdup(cmd_line->command);
	args_list = cmd_line->param;
	ft_lstadd_front(&args_list, ft_lstnew(arg));
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
	else if (cmd_line->command_num == EXPORT)
		return (export(cmd_line));
	else if (cmd_line->command_num == EXIT)
		ft_exit(cmd_line);
	else if((file_path = search_file(cmd_line->command)))
		return (run_binary(cmd_line));
	else if (!check_cmd_num(cmd_line))
		return (false);
	return (true);
}
