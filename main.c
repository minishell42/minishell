#include "minishell.h"

int			main(int argc, char **argv, char *envp[])
{
	char		*line;
	t_list		*command_lines;
	t_list		*env;

	env = get_env_llist(envp);
	while (true)
	{
		write(1, "minishell$ ", 12);
		get_next_line(0, &line);
		minishell(line, env);
		// command_lines = get_command_lines(line, env);

		// if (!run_command(command_lines, env))
		// {
		// 	ft_free(env);
		// 	ft_free(command_lines);
		// 	return (0);
		// }
		free(line);
	}
	return (0);
}
