#include "test.h"

char *get_err_msg(char *func_name, int case_number, char *expect, char *result)
{
	char *msg;

	msg = ft_calloc(sizeof(char), 200);
	sprintf(msg, "func_name = %s\ncase_number = %d\nexpect = %s\nresult = %s\n",
					func_name, case_number, expect, result);
	return (msg);
}

void check_command_line(t_cmd_line expect, t_cmd_line result)
{
	static int	case_number = 0;
	char 		*message;
	char		*name = "get_command_line";

	case_number++;
	if (!are_equal(expect.command, result.command))
	{
		message = get_err_msg(name, case_number, expect.command, result.command);
		message_and_exit(message, false);
	}
	if (!are_equal(expect.option, result.option))
	{
		message = get_err_msg(name, case_number, expect.option, result.option);
		message_and_exit(message, false);
	}
	if (!are_equal(expect.param, result.param))
	{
		message = get_err_msg(name, case_number, expect.param, result.param);
		message_and_exit(message, false);
	}
}

void test_get_command_line()
{

	t_cmd_line *cmd_line;

	char *case1= "echo -n 1234"; 
	t_cmd_line _case1 = {"echo", "-n", "1234"};
	cmd_line = get_command_line(&case1);
	check_command_line(_case1, *cmd_line);
	printf("====================  Case 1 OK  ==========================\n");

	char *case2= "echo 1234"; 
	t_cmd_line _case2 = {"echo", 0, "1234"};
	cmd_line = get_command_line(&case2);
	check_command_line(_case2, *cmd_line);
	printf("====================  Case 2 OK  ==========================\n");

	char *case3= "echo -n"; 
	t_cmd_line _case3 = {"echo", "-n", "\0"};
	cmd_line = get_command_line(&case3);
	check_command_line(_case3, *cmd_line);
	printf("====================  Case 3 OK  ==========================\n");

	char *case4= "echo -n 1234 1234"; 
	t_cmd_line _case4 = {"echo", "-n", "1234 1234"};
	cmd_line = get_command_line(&case4);
	check_command_line(_case4, *cmd_line);
	printf("====================  Case 4 OK  ==========================\n");
}
