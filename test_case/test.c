#include "test.h"

int main(int argc, char **argv, char *envp[])
{
	t_list *env;

	env = get_env_llist(envp);
	test_get_command_line(env);

	return (0);
}