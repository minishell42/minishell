#include "include/minishell.h"

int			main(int argc, char **argv, char *envp[])
{
	char		*line;
	t_list		*command_lines;
	// t_list		*env;

	g_env = get_env_llist(envp);
	// set_signal();
	signal(SIGINT, handler_signal);
	signal(SIGQUIT, handler_signal);
	while (true)
	{
		prompt();
		if (!get_next_line(0, &line))
			process_exit(1);
		else if (is_empty_line(line))
		{
			free(line);
			continue ;
		}
		minishell(line);
		free(line);
	}
	free_env_list(&g_env);
	return (0);
}
