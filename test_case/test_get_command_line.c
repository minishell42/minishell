#include "test.h"

char *get_err_msg(char *func_name, int case_number, char *expect, char *result)
{
	char *msg;

	msg = ft_calloc(sizeof(char), 200);
	sprintf(msg, "func_name = %s\ncase_number = %d\nexpect = '%s'\nresult = '%s'\n",
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
	char *expect_content;
	char *result_content;
	while (expect.redir_param)
	{
		expect_content = (char *)expect.redir_param->content;
		result_content = (char *)result.redir_param->content;
		if (!are_equal(expect_content, result_content))
		{
			message = get_err_msg(name, case_number, expect_content, result_content);
			message_and_exit(message, false);
		}
		expect.redir_param = expect.redir_param->next;
		result.redir_param = result.redir_param->next;
	}
	// if (!are_equal(expect.redir_param, result.redir_param))
	// {
	// 	printf("enter file\n");
	// 	message = get_err_msg(name, case_number, expect.redir_param, result.redir_param);
	// 	message_and_exit(message, false);
	// }
}

void test_get_command_line(t_list *env)
{

	t_cmd_line *cmd_line;
	char flag = 0;

	char *case1= "echo -n 1234"; 
	t_cmd_line _case1 = {"echo", "-n", "1234", 1, 0, 0, 0};
	cmd_line = get_command_line(&case1, &flag, env);
	check_command_line(_case1, *cmd_line);
	printf("====================  Case 1 OK  ==========================\n");

	char *case2= "echo 1234"; 
	t_cmd_line _case2 = {"echo", 0, "1234", 1, 0, 0, 0};
	flag = 0;
	cmd_line = get_command_line(&case2, &flag, env);
	check_command_line(_case2, *cmd_line);
	printf("====================  Case 2 OK  ==========================\n");

	char *case3= "echo -n"; 
	t_cmd_line _case3 = {"echo", "-n", "\0", 1, 0, 0, 0};
	flag = 0;
	cmd_line = get_command_line(&case3, &flag, env);
	check_command_line(_case3, *cmd_line);
	printf("====================  Case 3 OK  ==========================\n");

	char *case4= "echo -n 1234 1234"; 
	t_cmd_line _case4 = {"echo", "-n", "1234 1234", 1, 0, 0, 0};
	flag = 0;
	cmd_line = get_command_line(&case4, &flag, env);
	check_command_line(_case4, *cmd_line);
	printf("====================  Case 4 OK  ==========================\n");

	char *case5= "\"echo\" -n 1234 1234"; 
	t_cmd_line _case5 = {"echo", "-n", "1234 1234", 1, 0, 0, 0};
	flag = 0;
	cmd_line = get_command_line(&case5, &flag, env);
	check_command_line(_case5, *cmd_line);
	printf("====================  Case 5 OK  ==========================\n");
	
	char *case6= "e\"cho\" -n 1234 1234"; 
	t_cmd_line _case6 = {"echo", "-n", "1234 1234", 1, 0, 0, 0};
	flag = 0;
	cmd_line = get_command_line(&case6, &flag, env);
	check_command_line(_case6, *cmd_line);
	printf("====================  Case 6 OK  ==========================\n");

	char *case7= "echo -\"n\" 1234 1234"; 
	t_cmd_line _case7 = {"echo", "-n", "1234 1234", 1, 0, 0, 0};
	flag = 0;
	cmd_line = get_command_line(&case7, &flag, env);
	check_command_line(_case7, *cmd_line);
	printf("====================  Case 7 OK  ==========================\n");
	
	char *case8= "echo -n 1\"234\"; 1234"; 
	t_cmd_line _case8 = {"echo", "-n", "1234", 1, 0, 0, 0};
	flag = 0;
	cmd_line = get_command_line(&case8, &flag, env);
	check_command_line(_case8, *cmd_line);
	printf("====================  case8 OK  ==========================\n");

	char *case9= "echo -n 1234| echo 125"; 
	t_cmd_line _case9 = {"echo", "-n", "1234", 1, 1, 0, 0};
	flag = 0;
	cmd_line = get_command_line(&case9, &flag, env);
	check_command_line(_case9, *cmd_line);
	printf("====================  case9 OK  ==========================\n");

	char *case10= "echo 1234 > file"; 
	t_list	*expect = ft_lstnew("file");
	t_cmd_line _case10 = {"echo", 0, "1234", 1, 0, 1, expect};
	flag = 0;
	cmd_line = get_command_line(&case10, &flag, env);
	check_command_line(_case10, *cmd_line);
	printf("====================  case10 OK  ==========================\n");

	char *case11= "echo 1234 > file name is 42"; 
	t_list	*expect2 = ft_lstnew("name");
	t_list	*expect3 = ft_lstnew("is");
	t_list	*expect4 = ft_lstnew("42");
	ft_lstadd_back(&expect, expect2);
	ft_lstadd_back(&expect, expect3);
	ft_lstadd_back(&expect, expect4);
	t_cmd_line _case11 = {"echo", 0, "1234", 1, 0, 1, expect};
	flag = 0;
	cmd_line = get_command_line(&case11, &flag, env);
	check_command_line(_case11, *cmd_line);
	printf("====================  case11 OK  ==========================\n");

	char *case12= "echo 1234 > f\"ile\" name is 42";
	t_cmd_line _case12 = {"echo", 0, "1234", 1, 0, 1, expect};
	flag = 0;
	cmd_line = get_command_line(&case12, &flag, env);
	check_command_line(_case12, *cmd_line);
	printf("====================  case12 OK  ==========================\n");

	char *case13= "echo $ENV_TEST";
	t_cmd_line _case13 = {"echo", 0, "1234", 1, 0, 0, 0};
	ft_lstadd_back(&env, ft_lstnew("ENV_TEST=1234"));
	flag = 0;
	cmd_line = get_command_line(&case13, &flag, env);
	check_command_line(_case13, *cmd_line);
	printf("====================  case13 OK  ==========================\n");

	char *case14= "echo $ENV_TEST $ENV_TEST";
	t_cmd_line _case14 = {"echo", 0, "1234 1234", 1, 0, 0, 0};
	ft_lstadd_back(&env, ft_lstnew("ENV_TEST=1234"));
	flag = 0;
	cmd_line = get_command_line(&case14, &flag, env);
	check_command_line(_case14, *cmd_line);
	printf("====================  case14 OK  ==========================\n");

	char *case15= "echo $ENV_TEST$ENV_TEST $ENV_TEST";
	t_cmd_line _case15 = {"echo", 0, "12341234 1234", 1, 0, 0, 0};
	ft_lstadd_back(&env, ft_lstnew("ENV_TEST=1234"));
	flag = 0;
	cmd_line = get_command_line(&case15, &flag, env);
	check_command_line(_case15, *cmd_line);
	printf("====================  case15 OK  ==========================\n");

	char *case16= "$EC$HO $ENV_TEST$ENV_TEST $ENV_TEST";
	t_cmd_line _case16 = {"echo", 0, "12341234 1234", 1, 0, 0, 0};
	ft_lstadd_back(&env, ft_lstnew("EC=ec"));
	ft_lstadd_back(&env, ft_lstnew("HO=ho"));
	ft_lstadd_back(&env, ft_lstnew("ENV_TEST=1234"));
	flag = 0;
	cmd_line = get_command_line(&case16, &flag, env);
	check_command_line(_case16, *cmd_line);
	printf("====================  case16 OK  ==========================\n");

	char *case17= "$EC$HO $M$N $ENV_TEST$ENV_TEST $ENV_TEST";
	t_cmd_line _case17 = {"echo", "-n", "12341234 1234", 1, 0, 0, 0};
	ft_lstadd_back(&env, ft_lstnew("M=-"));
	ft_lstadd_back(&env, ft_lstnew("N=n"));
	flag = 0;
	cmd_line = get_command_line(&case17, &flag, env);
	check_command_line(_case17, *cmd_line);
	printf("====================  case17 OK  ==========================\n");
}