#include "test.h"


int		set_syntax_err(char *line, int i)
{
	char	*err_value;
	err_value = ft_calloc(sizeof(char), 3);
	err_value[0] = line[i];
	if (line[i] == line[i - 1] || line[i] == line[i + 1])
		err_value[1] = line[i];
	parsing_err_value(SYNTAX_ERROR, err_value);
	free(err_value);
	return (0);
}

int		check_start_line(char *line, int i)
{
	if (!line || !(*line))
		return (0);
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (line[i] == ';' || line[i] == '|')
		return (set_syntax_err(line, i));
	return (1);
}

int		validate_line(char *line)
{	
	int		i;
	char	flag;
	
	i = 0;
	flag = 0;
	if (!check_start_line(line, i))
		return (0);
	while (line[i])
	{
		while (line[i] && !is_delimitor(line[i]))
			i++;
		if (line[i] && !flag)
		{
			flag = line[i++];
			if (flag == '>' && line[i] == '>')
				i++;
		}
		while (ft_isspace(line[i]))
			i++;
//	"echo 123 | echo 454 ; ;;"
		if (flag && is_delimitor(line[i]))
			return (set_syntax_err(line, i));
		flag = 0;
		if (line[i])
			i++;
	}
	return (1);
}

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
		print_err_msg();
	printf("============ case3 OK =============\n");
	
	char *case4 = "echo ;123";

	if (validate_line(case4) != 1)
	{
		sprintf(tmp, "case4 is %s\n", case4);
		message_and_exit(tmp, false);
	}
	if (g_err.err_value)
		print_err_msg();
	printf("============ case4 OK =============\n");

	char *case5 = "echo 123;;";

	if (validate_line(case5) != 0)
	{
		sprintf(tmp, "case5 is %s\n", case5);
		message_and_exit(tmp, false);
	}
	if (g_err.err_value)
		print_err_msg();
	printf("============ case5 OK =============\n");

	char *case6 = "> echo 123";

	if (validate_line(case6) != true)
	{
		sprintf(tmp, "case6 is %s\n", case6);
		message_and_exit(tmp, false);
	}
	if (g_err.err_value)
		print_err_msg();
	printf("============ case6 OK =============\n");

	char *case7 = "echo 123 > >";

	if (validate_line(case7) != false)
	{
		sprintf(tmp, "case7 is %s\n", case7);
		message_and_exit(tmp, false);
	}
	if (g_err.err_value)
		print_err_msg();
	printf("============ case7 OK =============\n");

	char *case8 = "echo 123 > <";

	if (validate_line(case8) != false)
	{
		sprintf(tmp, "case8 is %s\n", case8);
		message_and_exit(tmp, false);
	}
	if (g_err.err_value)
		print_err_msg();
	printf("============ case8 OK =============\n");

	char *case9 = "echo 123 >> <";

	if (validate_line(case9) != false)
	{
		sprintf(tmp, "case9 is %s\n", case9);
		message_and_exit(tmp, false);
	}
	if (g_err.err_value)
		print_err_msg();
	printf("============ case9 OK =============\n");

	
	char *case10 = "| echo 123";

	if (validate_line(case10) != false)
	{
		sprintf(tmp, "case10 is %s\n", case10);
		message_and_exit(tmp, false);
	}
	if (g_err.err_value)
		print_err_msg();
	printf("============ case10 OK =============\n");


	char *case11 = "echo 123 |;";

	if (validate_line(case11) != false)
	{
		sprintf(tmp, "case11 is %s\n", case11);
		message_and_exit(tmp, false);
	}
	if (g_err.err_value)
		print_err_msg();
	printf("============ case11 OK =============\n");


	char *case12 = "echo 123 | echo 454 ; ;;";

	if (validate_line(case12) != false)
	{
		sprintf(tmp, "case12 is %s\n", case12);
		message_and_exit(tmp, false);
	}
	if (g_err.err_value)
		print_err_msg();
	printf("============ case12 OK =============\n");

	char *case13 = "echo 123 | echo 454 ; echo 123 > >> 2";

	if (validate_line(case13) != false)
	{
		sprintf(tmp, "case13 is %s\n", case13);
		message_and_exit(tmp, false);
	}
	if (g_err.err_value)
		print_err_msg();
	printf("============ case13 OK =============\n");

	free(tmp);
}

int main(int argc, char **argv, char *envp[])
{
	// t_list *env;

	// if (argc != 1)
		// return (0);
	// argv[1] = 0;
	// env = get_env_llist(envp);
	// test_get_command_line(env);
	// test_command_lines(env);
	// ft_lstclear(&env, free);

	test_validate_line();
	return (0);
}

