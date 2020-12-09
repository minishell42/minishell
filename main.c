#include "minishell.h"




// void		test_env_llist()
// {
// 	char *case1[4] = {"v1=1", "v2=2", "v3=3", 0};
	
// 	t_list *res = get_env_llist(case1);
// 	int i = 0;
// 	while (case1[i])
// 	{
// 		if (!are_equal(res->content, case1[i]))
// 			exit(1);
// 		i++;
// 		res = res->next;
// 		printf("loop\n");
// 	}
// 	printf("done\n");
// }

int			main(int argc, char **argv, char *envp[])
{
	char		*line;
	t_list		*command_lines;
	t_list		*env;

	env = get_env_llist(envp);
	// test_env_llist();
	while (true)
	{
		write(1, "minishell$ ", 12);
		get_next_line(0, &line);
		command_lines = get_command_lines(line, env);

		// if (!run_command(command_lines, env))
		// {
		// 	ft_free(env);
		// 	ft_free(command_lines);
		// 	return (0);
		// }
	}
	return (0);
}
