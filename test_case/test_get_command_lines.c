#include "test.h"

void	check_command_lines(t_list *cmd)
{
	t_cmd_line *tmp;
	int			i;
	int			index;
	char		*redir_param;

	index = 1;
	tmp = (cmd->content);
	while (cmd && tmp)
	{
		printf("+++++++ while start +++++++++\n");
		printf("struct index : %d\n", index);
		printf("command : %s\n", tmp->command);
		printf("command_num : %d\n", tmp->command_num);
		printf("option : %s\n", tmp->option);
		printf("param : %s\n", tmp->param);
		printf("pipe_flag : %d\n", tmp->pipe_flag);
		printf("redir_flag : %d\n", tmp->redir_flag);
		i = 1;
		while (tmp->redir_param)
		{
			redir_param = (char *)(tmp->redir_param->content);
			printf("redir_param index : %d", i);
			printf("redir_param : %s\n", redir_param);
			i++;
			tmp->redir_param = tmp->redir_param->next;
		}
		index++;
		cmd = cmd->next;
		if (cmd)
			tmp = cmd->content;
		printf("+++++++ while end +++++++++\n");
	}
}

void	test_command_lines(t_list *env)
{
	// count
	t_list *cmd_lines;
	t_list	*tmp;
	int expect_size;
	t_list *start;

	char *case1= "echo -n 1234 ; echo -n 1234"; 
	expect_size = 2;
	cmd_lines = get_command_lines(case1, env);
	start = cmd_lines;
	if (expect_size != ft_lstsize(cmd_lines))
		check_command_lines(cmd_lines);
	while(start)
	{
		t_list *start2 = start;
		tmp = start->content;
		free_cmd_struct(start->content);
		start = start->next;
		free(start2);
		free(tmp);
	}
	printf("====================  Case 1 OK  ==========================\n");

	char *case2= "echo -n 1234 | echo -n 1234"; 
	// expect_size = 2;
	cmd_lines = get_command_lines(case2, env);
	start = cmd_lines;
	// if (expect_size != ft_lstsize(cmd_lines))
		check_command_lines(cmd_lines);
	// free(cmd_lines);
	while(start)
	{
		t_list *start2 = start;
		tmp = start->content;
		free_cmd_struct(start->content);
		start = start->next;
		free(start2);
		free(tmp);
	}
	printf("====================  case2 OK  ==========================\n");

	// char *case3= "echo -n 1234| echo -n 1234 | echo -n 1234"; 
	// // expect_size = 2;
	// cmd_lines = get_command_lines(case3, env);
	// start = cmd_lines;
	// // if (expect_size != ft_lstsize(cmd_lines))
	// 	check_command_lines(cmd_lines);
	// // free(cmd_lines);
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
	// // expect_size = 2;
	// cmd_lines = get_command_lines(case4, env);
	// start = cmd_lines;
	// // if (expect_size != ft_lstsize(cmd_lines))
	// 	check_command_lines(cmd_lines);
	// // free(cmd_lines);
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
	// // expect_size = 2;
	// cmd_lines = get_command_lines(case5, env);
	// start = cmd_lines;
	// // if (expect_size != ft_lstsize(cmd_lines))
	// 	check_command_lines(cmd_lines);
	// // free(cmd_lines);
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
	// // expect_size = 2;
	// cmd_lines = get_command_lines(case6, env);
	// start = cmd_lines;
	// // if (expect_size != ft_lstsize(cmd_lines))
	// 	check_command_lines(cmd_lines);
	// // free(cmd_lines);
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