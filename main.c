#include "minishell.h"

static void	argv_err(int argc, char **argv)
{
	if (argc != 1)
	{
		write(1, "error : ", 9);
		write(1, argv[0], ft_strlen(argv[0]));
		exit(1);
	}
}

int			main(int argc, char **argv, char *envp[])
{
	char		*line;

	argv_err(argc, argv);
	g_env = get_env_llist(envp);
	set_exit_status(EXIT_SUCCESS);
	while (true)
	{
		init_signal();
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
	if (g_env)
		free_env_list(&g_env);
	return (0);
}
