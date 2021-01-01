#include "test.h"

int main(int argc, char **argv, char *envp[])
{
	if (argc != 1)
		return (0);
	argv[1] = 0;
	g_env = get_env_llist(envp);
	// test_get_command_line(env);
	// test_cd(env);
	//  test_command_lines(env);
	// test_redirection(env);
	// test_validate_line();
	test_export();
	test_env();
	test_unset();
	ft_lstclear(&g_env, free);

	return (0);
}

