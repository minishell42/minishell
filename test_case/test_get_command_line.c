#include "test.h"

char *get_err_msg(char *func_name, int case_number, char *expect, char *result)
{
	char *msg;

	msg = ft_calloc(sizeof(char), 200);
	sprintf(msg, "func_name = %s\ncase_number = %d\nexpect = %s\nresult = %s\n",
					func_name, case_number, expect, result);
	return (msg);
}

char *get_err_msg_int(char *func_name, int case_number, int expect, int result)
{
	char *msg;

	msg = ft_calloc(sizeof(char), 200);
	sprintf(msg, "func_name = %s\ncase_number = %d\nexpect = %d\nresult = %d\n",
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
	if (expect.command_num != result.command_num)
	{
		message = get_err_msg_int(name, case_number, expect.command_num, result.command_num);
		message_and_exit(message, false);
	}
	if (expect.pipe_flag != result.pipe_flag)
	{
		message = get_err_msg_int(name, case_number, expect.pipe_flag, result.pipe_flag);
		message_and_exit(message, false);
	}
	if (expect.redir_flag != result.redir_flag)
	{
		message = get_err_msg_int(name, case_number, expect.redir_flag, result.redir_flag);
		message_and_exit(message, false);
	}
	if (!are_equal(expect.redir_file, result.redir_file))
	{
		printf("enter file\n");
		message = get_err_msg(name, case_number, expect.redir_file, result.redir_file);
		message_and_exit(message, false);
	}
}

void test_get_command_line()
{

	t_cmd_line *cmd_line;
	char flag = 0;

	char *case1= "echo -n 1234"; 
	t_cmd_line _case1 = {"echo", "-n", "1234", 1, 0, 0, 0};
	cmd_line = get_command_line(&case1, &flag);
	check_command_line(_case1, *cmd_line);
	printf("====================  Case 1 OK  ==========================\n");

	char *case2= "echo 1234"; 
	t_cmd_line _case2 = {"echo", 0, "1234", 1, 0, 0, 0};
	flag = 0;
	cmd_line = get_command_line(&case2, &flag);
	check_command_line(_case2, *cmd_line);
	printf("====================  Case 2 OK  ==========================\n");

	char *case3= "echo -n"; 
	t_cmd_line _case3 = {"echo", "-n", "\0", 1, 0, 0, 0};
	flag = 0;
	cmd_line = get_command_line(&case3, &flag);
	check_command_line(_case3, *cmd_line);
	printf("====================  Case 3 OK  ==========================\n");

	char *case4= "echo -n 1234 1234"; 
	t_cmd_line _case4 = {"echo", "-n", "1234 1234", 1, 0, 0, 0};
	flag = 0;
	cmd_line = get_command_line(&case4, &flag);
	check_command_line(_case4, *cmd_line);
	printf("====================  Case 4 OK  ==========================\n");

	char *case5= "\"echo\" -n 1234 1234"; 
	t_cmd_line _case5 = {"echo", "-n", "1234 1234", 1, 0, 0, 0};
	flag = 0;
	cmd_line = get_command_line(&case5, &flag);
	check_command_line(_case5, *cmd_line);
	printf("====================  Case 5 OK  ==========================\n");
	
	char *case6= "e\"cho\" -n 1234 1234"; 
	t_cmd_line _case6 = {"echo", "-n", "1234 1234", 1, 0, 0, 0};
	flag = 0;
	cmd_line = get_command_line(&case6, &flag);
	check_command_line(_case6, *cmd_line);
	printf("====================  Case 6 OK  ==========================\n");

	char *case7= "echo -\"n\" 1234 1234"; 
	t_cmd_line _case7 = {"echo", "-n", "1234 1234", 1, 0, 0, 0};
	flag = 0;
	cmd_line = get_command_line(&case7, &flag);
	check_command_line(_case7, *cmd_line);
	printf("====================  Case 7 OK  ==========================\n");
	
	char *case8= "echo -n 1\"234\"; 1234"; 
	t_cmd_line _case8 = {"echo", "-n", "1234", 1, 0, 0, 0};
	flag = 0;
	cmd_line = get_command_line(&case8, &flag);
	check_command_line(_case8, *cmd_line);
	printf("====================  case8 OK  ==========================\n");

	char *case9= "echo -n 1234| echo 125"; 
	t_cmd_line _case9 = {"echo", "-n", "1234", 1, 1, 0, 0};
	flag = 0;
	cmd_line = get_command_line(&case9, &flag);
	check_command_line(_case9, *cmd_line);
	printf("====================  case9 OK  ==========================\n");

	char *case10= "echo 1234 > file"; 
	t_cmd_line _case10 = {"echo", 0, "1234", 1, 0, 1, "file"};
	flag = 0;
	cmd_line = get_command_line(&case10, &flag);
	check_command_line(_case10, *cmd_line);
	printf("====================  case10 OK  ==========================\n");
	// char *case8= "echo \"-n\" 1234 1234"; 
	// t_cmd_line _case8 = {"echo", "-n", "1234 1234"};
	// flag = 0;
	// cmd_line = get_command_line(&case8, &flag);
	// check_command_line(_case8, *cmd_line);
	// printf("====================  case8 OK  ==========================\n");
}
