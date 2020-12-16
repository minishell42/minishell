#include "test.h"

void	test_redirection(t_list *env)
{
	t_cmd_line *cmd_line;

	char *case1 = "echo 123 > 123";
	cmd_line = get_command_line(&case1, env);
	redirection(cmd_line, env, "123\n");
	free_cmd_struct(cmd_line);
	free(cmd_line);
	printf("================ case1 OK ==============\n");

	char *case2 = "echo 123 >> 123";
	cmd_line = get_command_line(&case2, env);
	redirection(cmd_line, env, "123\n");
	free_cmd_struct(cmd_line);
	free(cmd_line);
	printf("================ case2 OK ==============\n");

	char *case3 = "echo 456 > 123";
	cmd_line = get_command_line(&case3, env);
	redirection(cmd_line, env, "456\n");
	free_cmd_struct(cmd_line);
	free(cmd_line);
	printf("================ case3 OK ==============\n");

	char *case4 = "> 123";
	cmd_line = get_command_line(&case4, env);
	redirection(cmd_line, env, "");
	free_cmd_struct(cmd_line);
	free(cmd_line);
	printf("================ case4 OK ==============\n");

	char *case5 = "123 >";
	cmd_line = get_command_line(&case5, env);
	redirection(cmd_line, env, "");
	free_cmd_struct(cmd_line);
	free(cmd_line);
	printf("================ case5 OK ==============\n");
}