#include "command.h"

static char	**make_exec_args(t_cmd_line *cmd_line)
{
	char	**args;
	char	**split_param;
	char	*param;
	int		len;
	int		index;

	len = 1;
	index = 0;
	param = cmd_line->param;
	while (param[index] && check_character_in_line(param, &index, ft_isspace))
		len++;
	args = ft_calloc(sizeof(char *), len + 1);
	args[0] = ft_strdup(cmd_line->command);
	index = 0;
	split_param = ft_split(param, ' ');
	while (split_param[index])
	{
		args[index + 1] = ft_strdup(split_param[index]);
		index++;
	}
	free_str_array(split_param);
	args[index + 1] = NULL;
	return (args);
}


static bool	run_binary(t_cmd_line *cmd_line, t_list *env)
{
	char	*root;
	char 	*file_path;
	char	**envp;
	char	**args;

	envp = convert_to_array_env_list(env);
	args = make_exec_args(cmd_line);
	if (execve(file_path, args, envp) == -1)
		return (false);
	return (true);
}

// bool		run_command(t_cmd_line *cmd_line, t_list *env, char *pipe_input)
// {
// 	char		*file_path;

// 	if (cmd_line->command_num == ECHO)
// 		return (echo(cmd_line, env, pipe_input));
// 	// else if (cmd_line->command_num == CD)
// 	// 	cd(cmd_line, env, pipe_input);
// 	// else if (cmd_line->command_num == PWD)
// 	// 	pwd(cmd_line, &pipe_input);
// 	// else if (cmd_line->command_num == EXPORT)
// 	// 	export(cmd_line, env, pipe_input);
// 	// else if (cmd_line->command_num == EXIT)
// 	// 	ft_exit(cmd_line, env, &pipe_input);
// 	if((file_path = search_file(cmd_line->command, env)))
// 		return (run_binary(cmd_line, env));
// 	else if (!check_cmd_num(cmd_line))
// 		return (false);
// 	return (true);
// }

bool		run_command(t_cmd_line *cmd_line, t_list *env)
{
	char		*file_path;

	if (cmd_line->command_num == ECHO)
		return (echo(cmd_line, env));
	// else if (cmd_line->command_num == CD)
	// 	cd(cmd_line, env);
	else if (cmd_line->command_num == PWD)
		pwd(cmd_line);
	// else if (cmd_line->command_num == EXPORT)
	// 	export(cmd_line, env);
	// else if (cmd_line->command_num == EXIT)
	// 	ft_exit(cmd_line, env);
	if((file_path = search_file(cmd_line->command, env)))
		return (run_binary(cmd_line, env));
	else if (!check_cmd_num(cmd_line))
		return (false);
	return (true);
}
