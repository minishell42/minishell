#include "test.h"

void	test_validate_line()
{
	char *case1 = "";
	char *tmp;

	tmp = ft_calloc(sizeof(char), 255);
	if (validate_line(case1) != 0)
	{
		sprintf(tmp, "case1 is %s\n", case1);
		message_and_exit(tmp, false);
	}
	if (g_err.err_value)
		print_err_msg();
	printf("============ case1 OK =============\n");

	char *case2 = "echo 123";

	if (validate_line(case2) != 1)
	{
		sprintf(tmp, "case2 is %s\n", case2);
		message_and_exit(tmp, false);
	}
	if (g_err.err_value)
		print_err_msg();
	printf("============ case2 OK =============\n");

	char *case3 = ";echo 123";

	if (validate_line(case3) != 0)
	{
		sprintf(tmp, "case3 is %s\n", case3);
		message_and_exit(tmp, false);
	}
	if (g_err.err_value)
	{
		print_err_msg();
		printf(" is result.     expect = '%s'\n", ";");
	}
	printf("============ case3 OK =============\n");
	
	char *case4 = "echo ;123";

	if (validate_line(case4) != 1)
	{
		sprintf(tmp, "case4 is %s\n", case4);
		message_and_exit(tmp, false);
	}
	if (g_err.err_value)
	{
		print_err_msg();
		printf(" is result.     expect = '%s'\n", ";");

	}
	printf("============ case4 OK =============\n");

	char *case5 = "echo 123;;";

	if (validate_line(case5) != 0)
	{
		sprintf(tmp, "case5 is %s\n", case5);
		message_and_exit(tmp, false);
	}
	// printf("err_value : %s\n", g_err.err_value);
	if (g_err.err_value)
	{
		print_err_msg();
		printf(" is result.     expect = '%s'\n", ";;");
	}
	printf("============ case5 OK =============\n");

	char *case6 = "> echo 123";

	if (validate_line(case6) != true)
	{
		sprintf(tmp, "case6 is %s\n", case6);
		message_and_exit(tmp, false);
	}
	if (g_err.err_value)
	{
		print_err_msg();
		printf(" is result.     expect = '%s'\n", "");
	}
	printf("============ case6 OK =============\n");

	char *case7 = "echo 123 > >";

	if (validate_line(case7) != false)
	{
		sprintf(tmp, "case7 is '%s'\n", case7);
		message_and_exit(tmp, false);
	}
	if (g_err.err_value)
	{
		print_err_msg();
		printf(" is result.     expect = '%s'\n", ">");
	}
	printf("============ case7 OK =============\n");

	char *case8 = "echo 123 > <";

	if (validate_line(case8) != false)
	{
		sprintf(tmp, "case8 is '%s'\n", case8);
		message_and_exit(tmp, false);
	}
	if (g_err.err_value)
	{
		print_err_msg();
		printf(" is result.     expect = '%s'\n", "<");

	}
	printf("============ case8 OK =============\n");

	char *case9 = "echo 123 >> <";

	if (validate_line(case9) != false)
	{
		sprintf(tmp, "case9 is '%s'\n", case9);
		message_and_exit(tmp, false);
	}
	if (g_err.err_value)
	{
		print_err_msg();
		printf(" is result.     expect = '%s'\n", "<");
	}
	printf("============ case9 OK =============\n");

	
	char *case10 = "| echo 123";

	if (validate_line(case10) != false)
	{
		sprintf(tmp, "case10 is '%s'\n", case10);
		message_and_exit(tmp, false);
	}
	if (g_err.err_value)
	{
		print_err_msg();
		printf(" is result.     expect = '%s'\n", "|");
	}
	printf("============ case10 OK =============\n");


	char *case11 = "echo 123 |;";

	if (validate_line(case11) != false)
	{
		sprintf(tmp, "case11 is '%s'\n", case11);
		message_and_exit(tmp, false);
	}
	if (g_err.err_value)
	{
		print_err_msg();
		printf(" is result.     expect = '%s'\n", ";");
	}
	printf("============ case11 OK =============\n");


	char *case12 = "echo 123 | echo 454 ; ;;";

	if (validate_line(case12) != false)
	{
		sprintf(tmp, "case12 is '%s'\n", case12);
		message_and_exit(tmp, false);
	}
	if (g_err.err_value)
	{
		print_err_msg();
		printf(" is result.     expect = '%s'\n", ";;");
	}
	printf("============ case12 OK =============\n");

	char *case13 = "echo 123 | echo 454 ; echo 123 > >> 2";

	if (validate_line(case13) != false)
	{
		sprintf(tmp, "case13 is '%s'\n", case13);
		message_and_exit(tmp, false);
	}
	if (g_err.err_value)
	{
		print_err_msg();
		printf(" is result.     expect = '%s'\n", ">>");
	}
	printf("============ case13 OK =============\n");

	free(tmp);
}
