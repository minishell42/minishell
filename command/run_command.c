#include "command.h"

static char	**make_exec_args(t_cmd_line *cmd_line)
{
	char	**envp;
	int		len;
	char	**args;

	len = 1;
	if (*(cmd_line->param))
		len++;
	args = ft_calloc(sizeof(char *), len + 1);
	args[0] = cmd_line->command;
	if (*(cmd_line->param))
	{
		args[1] = cmd_line->param;
		args[2] = NULL;
	}
	else if (cmd_line->redir_flag == REDIR_IN) // 123 file : 4567 // cat < 123 -> 4567 출력 //
	{
		args[1] = (char *)(cmd_line->redir_param->content);
		args[2] = NULL;
	}
	else
		args[1] = NULL;
	return (args);
}



char	*run_command(t_cmd_line *cmd_line, t_list *env, char *pipe_input)
{
	char		*result;

	result = NULL;
	// if (!check_cmd_num(cmd_line))
	// {
	// 	print_err_msg();
	// 	// free_pipe_input(&pipe_input);
	// 	return (NULL);
	// }
	if (cmd_line->command_num == ECHO)
		result = echo(cmd_line, env, pipe_input);
	else if (cmd_line->command_num == CD)
		result = cd(cmd_line, env, pipe_input);
	else if (cmd_line->command_num == PWD)
		result = pwd(cmd_line, &pipe_input);
	else if (cmd_line->command_num == EXPORT)
		result = export(cmd_line, env, pipe_input);
	else if (cmd_line->command_num == EXIT)
		result = ft_exit(cmd_line, env, &pipe_input);
	else
	{
		char	*root = "/bin/";
		char 	*file_path;
		char	**envp;
		// int		len;
		char	**args;

		file_path = ft_strjoin(root, cmd_line->command);
		envp = convert_to_array_env_list(env);
		args = make_exec_args(cmd_line);
		// len = 1;
		printf("param : '%s'\n", cmd_line->param);
		printf("pipe_input : '%s'\n", pipe_input);
		// if (*(cmd_line->param))
		// 	len++;
		// args = ft_calloc(sizeof(char *), len + 1);
		// args[0] = cmd_line->command;
		// if (*(cmd_line->param))
		// {
		// 	printf("in\n");
		// 	args[1] = cmd_line->param;
		// 	args[2] = NULL;
		// }
		// else if (cmd_line->redir_flag == REDIR_IN)
		// {
		// 	args[1] = (char *)(cmd_line->redir_param->content);
		// 	args[2] = NULL;
		// }
		// else
		// {
		// 	args[1] = NULL;
		// }
		
		if (execve(file_path, args, envp) == -1)
			perror("excve\n");
	}
	return (result);
}
