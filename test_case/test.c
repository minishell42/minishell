#include "test.h"

int main(int argc, char **argv, char *envp[])
{
	t_list *env;

	if (argc != 1)
		return (0);
	argv[1] = 0;
	env = get_env_llist(envp);
	// test_get_command_line(env);
	// test_cd(env);
	 test_command_lines(env);
	// test_redirection(env);
	// test_validate_line();

	test_export(env);

	ft_lstclear(&env, free);

	return (0);
}

