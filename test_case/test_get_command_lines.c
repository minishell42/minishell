#include "test.h"

// void	check_command_lines(t_list *cmd)
// {
// 	t_cmd_line *tmp;
// 	int			i;
// 	int			index;
// 	char		*redir_param;

// 	index = 1;
// 	if (cmd)
// 		tmp = (cmd->content);
// 	else
// 		tmp = NULL;
// 	while (cmd && tmp)
// 	{
// 		printf("+++++++ while start +++++++++\n");
// 		printf("struct index : %d\n", index);
// 		printf("command : %s\n", tmp->command);
// 		printf("command_num : %d\n", tmp->command_num);
// 		printf("option : %s\n", tmp->option);
// 		printf("param : %s\n", tmp->param);
// 		printf("pipe_flag : %d\n", tmp->pipe_flag);
// 		printf("redir_flag : %d\n", tmp->redir_flag);
// 		i = 1;
// 		while (tmp->redir_param)
// 		{
// 			redir_param = (char *)(tmp->redir_param->content);
// 			printf("redir_param index : %d", i);
// 			printf("redir_param : %s\n", redir_param);
// 			i++;
// 			tmp->redir_param = tmp->redir_param->next;
// 		}
// 		index++;
// 		cmd = cmd->next;
// 		if (cmd)
// 			tmp = cmd->content;
// 		printf("+++++++ while end +++++++++\n");
// 	}
// }

void	check_command_lines(t_list *cmd)
{
	t_cmd_line *tmp;
	int			i;
	int			index;
	t_redir		*redir_param;
	t_list		*rd;

	index = 1;
	if (cmd)
		tmp = (cmd->content);
	else
		tmp = NULL;
	while (cmd && tmp)
	{
		printf("+++++++ while start +++++++++\n");
		printf("struct index : %d\n", index);
		printf("command : %s\n", tmp->command);
		printf("command_num : %d\n", tmp->command_num);
		printf("option : %s\n", tmp->option);
		printf("param : %s\n", tmp->param);
		printf("pipe_flag : %d\n", tmp->pipe_flag);
		i = 1;
		rd = tmp->redir_param;
		while (tmp->redir_param)
		{
			redir_param = (t_redir *)(tmp->redir_param->content);
			printf("redir_flag : %d\n", redir_param->redir_flag);
			printf("redir_param index : %d", i);
			printf("redir_param : %s\n", redir_param->redir_param);
			i++;
			tmp->redir_param = tmp->redir_param->next;
		}
		tmp->redir_param = rd;
		index++;
		cmd = cmd->next;
		if (cmd)
			tmp = cmd->content;
		printf("+++++++ while end +++++++++\n");
	}
}

void	free_list(t_list *start)
{
	t_list	*tmp;

	while(start)
	{
		t_list *start2 = start;
		tmp = start->content;
		free_cmd_struct(start->content);
		start = start->next;
		free(start2);
		free(tmp);
	}
}

t_list	*make_list(char *case_id, t_list *env)
{
	t_list *cmd_lines;
	t_cmd_line *cmd_line;

	cmd_lines = NULL;
	while (*case_id)
	{
		if (!(cmd_line = get_command_line(&case_id, env)))
		{
			built_in_error();
			return (cmd_lines);
		}
		if (cmd_lines)
			ft_lstadd_back(&cmd_lines, ft_lstnew(cmd_line));
		else
			cmd_lines = ft_lstnew(cmd_line);
	}
	return (cmd_lines);
}


void	test_command_lines(t_list *env)
{
	// count
	t_list *cmd_lines;
	t_list	*tmp;
	t_list *start;

	char *case1= "echo 123 > 123 > 456 ; echo 444"; 
	cmd_lines = make_list(case1, env);
	check_command_lines(cmd_lines);
	free_list(cmd_lines);
	printf("====================  Case 1 OK  ==========================\n");

	char *case2= "echo -n 1234 | echo -n 12345"; 
	cmd_lines = make_list(case2, env);
	check_command_lines(cmd_lines);
	free_list(cmd_lines);
	printf("====================  case2 OK  ==========================\n");

	char *case3= "echo -n 1234 > 123 < 456 > 123 | echo -n 12345"; 
	cmd_lines = make_list(case3, env);
	check_command_lines(cmd_lines);
	free_list(cmd_lines);
	printf("====================  case3 OK  ==========================\n");

	char *case4= "echo -n 1234 > 123 < "; 
	cmd_lines = make_list(case4, env);
	check_command_lines(cmd_lines);
	free_list(cmd_lines);
	printf("====================  case4 OK  ==========================\n");

	char *case5= "echo -n 1234 > 123 < >"; 
	cmd_lines = make_list(case5, env);
	check_command_lines(cmd_lines);
	free_list(cmd_lines);
	printf("====================  case5 OK  ==========================\n");

	char *case6= "echo -n 1234 > 123 333"; 
	cmd_lines = make_list(case6, env);
	check_command_lines(cmd_lines);
	free_list(cmd_lines);
	printf("====================  case6 OK  ==========================\n");

	char *case7= "$EC$HO $ENV_TEST$ENV_TEST > $ENV_TEST $ENV_TEST >>";
	ft_lstadd_back(&env, ft_lstnew(ft_strdup("EC=ec")));
	ft_lstadd_back(&env, ft_lstnew(ft_strdup("HO=ho")));
	ft_lstadd_back(&env, ft_lstnew(ft_strdup("ENV_TEST=1234")));
	cmd_lines = make_list(case7, env);
	check_command_lines(cmd_lines);
	free_list(cmd_lines);
	printf("====================  case7 OK  ==========================\n");

	char *case8= "$EC$HO $ENV_TEST$ENV_TEST > $ENV_TEST $ENV_TEST";
	ft_lstadd_back(&env, ft_lstnew(ft_strdup("EC=ec")));
	ft_lstadd_back(&env, ft_lstnew(ft_strdup("HO=ho")));
	ft_lstadd_back(&env, ft_lstnew(ft_strdup("ENV_TEST=1234")));
	cmd_lines = make_list(case8, env);
	check_command_lines(cmd_lines);
	free_list(cmd_lines);
	printf("====================  case8 OK  ==========================\n");

	char *case9= "echo -n 1234 >> 123 > 333"; 
	cmd_lines = make_list(case9, env);
	check_command_lines(cmd_lines);
	free_list(cmd_lines);
	printf("====================  case9 OK  ==========================\n");

	char *case10= "echo -n 1234 > 123 >> 333"; 
	cmd_lines = make_list(case10, env);
	check_command_lines(cmd_lines);
	free_list(cmd_lines);
	printf("====================  case10 OK  ==========================\n");

	char *case11= "echo -n 1234 ; echo 123 >> "; 
	cmd_lines = make_list(case11, env);
	check_command_lines(cmd_lines);
	free_list(cmd_lines);
	printf("====================  case11 OK  ==========================\n");

	// char *case3= "echo -n 1234| echo -n 1234 | echo -n 1234"; 
	// expect_size = 3;
	// cmd_lines = get_command_lines(case3, env);
	// start = cmd_lines;
	// if (expect_size != ft_lstsize(cmd_lines))
	// 	check_command_lines(cmd_lines);
	// while(start)
	// {
	// 	t_list *start2 = start;
	// 	tmp = start->content;
	// 	free_cmd_struct(start->content);
	// 	free(start2);
	// 	start = start->next;
	// 	free(tmp);
	// }
	// printf("====================  case3 OK  ==========================\n");

	// char *case4= "cma -n 1234| echo -n 1234 ; echo -n 1234"; 
	// expect_size = 0;
	// cmd_lines = get_command_lines(case4, env);
	// start = cmd_lines;
	// if (expect_size != ft_lstsize(cmd_lines))
	// 	check_command_lines(cmd_lines);
	// while(start)
	// {
	// 	t_list *start2 = start;
	// 	tmp = start->content;
	// 	free_cmd_struct(start->content);
	// 	free(start2);
	// 	start = start->next;
	// 	free(tmp);
	// }
	// printf("====================  case4 OK  ==========================\n");

	// char *case5= "cd -n 1234 | an -n 1234 | echo -n 1234"; 
	// expect_size = 1;
	// cmd_lines = get_command_lines(case5, env);
	// start = cmd_lines;
	// if (expect_size != ft_lstsize(cmd_lines))
	// 	check_command_lines(cmd_lines);
	// while(start)
	// {
	// 	t_list *start2 = start;
	// 	tmp = start->content;
	// 	free_cmd_struct(start->content);
	// 	free(start2);
	// 	start = start->next;
	// 	free(tmp);
	// }
	// printf("====================  case5 OK  ==========================\n");

	// char *case6= "cd -n 1234| export -n 1234 | eee -n 1234"; 
	// expect_size = 2;
	// cmd_lines = get_command_lines(case6, env);
	// start = cmd_lines;
	// if (expect_size != ft_lstsize(cmd_lines))
	// 	check_command_lines(cmd_lines);
	// while(start)
	// {
	// 	t_list *start2 = start;
	// 	tmp = start->content;
	// 	free_cmd_struct(start->content);
	// 	free(start2);
	// 	start = start->next;
	// 	free(tmp);
	// }
	// printf("====================  case6 OK  ==========================\n");
}