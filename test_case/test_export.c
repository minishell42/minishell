#include "test.h"

void ft_lstdel_last(t_list *lst, void (*del)(void *))
{
	int size;
	int i;
	t_list *last;

	size = ft_lstsize(lst);
	if (size && size < 2)
	{
		ft_lstdelone(lst, del);
		return ;
	}

	i = 1;
	while (i < size - 1)
	{
		lst = lst->next;
		i++;
	}
	last = lst->next;
	lst->next = 0;
	ft_lstdelone(last, del);
}

void test_export()
{
	char 		*case1 = "export a=1";
	char 		*expect1 = "a=1";
	t_cmd_line	*cmd_line1 = get_command_line(&case1);
	
	printf("command : '%s'\n", cmd_line1->command);
	export(cmd_line1);
	t_list *result1 = find_env_target_list("a");
	if (!result1)
		printf("no result\n");
	if (!are_equal(expect1, (char *)(result1->content)))
		message_and_exit((char *)(result1->content), false);
	ft_lstdel_last(g_env, free);
	free_cmd_struct(cmd_line1);
	printf("==============  case1 OK ==============\n");


	char		*case2 = "export a=";
	char		*expect2 = "a=";
	t_cmd_line	*cmd_line2 = get_command_line(&case2);

	export(cmd_line2);
	t_list *result2 = find_env_target_list("a");
	if (!are_equal(expect2, result2->content))
		message_and_exit(result2->content, false);
	ft_lstdel_last(g_env, free);
	free_cmd_struct(cmd_line2);
	printf("==============  case2 OK ==============\n");


	char		*case3 = "export a=1 c b=2";
	char		*expect3 = "a=1";
	char		*expect3_1 = "b=2";
	t_cmd_line	*cmd_line3 = get_command_line(&case3);

	if (export(cmd_line3))
		printf("return ok\n");
	else
		printf("return must be true!!!!!\n");
	t_list *result3 = find_env_target_list("a");
	t_list *result3_1 = find_env_target_list("b");

	if (!are_equal(expect3, result3->content))
		message_and_exit(result3->content, false);
	if (!are_equal(expect3_1, result3_1->content))
		message_and_exit(result3_1->content, false);
	print_err_msg();
	ft_lstdel_last(g_env, free);
	ft_lstdel_last(g_env, free);
	free_cmd_struct(cmd_line3);
	printf("==============  case3 OK ==============\n");



	char		*case4 = "export =";
	char		*expect4 = 0;
	t_cmd_line	*cmd_line4 = get_command_line(&case4);

	t_list *before_last = ft_lstlast(g_env);
	export(cmd_line4);
	
	if (before_last != ft_lstlast(g_env))
		exit(1);
	print_err_msg();

	free_cmd_struct(cmd_line4);
	printf("==============  case4 ok ==============\n");


	char		*case5 = "export abc@=3";
	t_cmd_line	*cmd_line5 = get_command_line(&case5);

	t_list *before_last5 = ft_lstlast(g_env);
	if (!export(cmd_line5))
		printf("export ok\n");
	else
		printf("result must be fail!!!!!\n");
	
	if (before_last5 != ft_lstlast(g_env))
	{
		printf("last content = %s\n", ((char *)ft_lstlast(g_env)->content));
		exit(1);
	}
	print_err_msg();

	free_cmd_struct(cmd_line5);
	printf("==============  case5 ok ==============\n");


	char		*case6 = "export abc+=3";
	char		*case6_1 = "export abc=3";

	t_cmd_line	*cmd_line6 = get_command_line(&case6);
	t_cmd_line	*cmd_line6_1 = get_command_line(&case6_1);

	if (!export(cmd_line6_1))
		printf("export 6_1 is fail\n");
	if (!export(cmd_line6))
	{
		printf("export 6 is fail\n");
		print_err_msg();
	}

	t_list *result6 = find_env_target_list("abc");
	if (!result6)
		printf("no result\n");

	if (!are_equal((char *)(result6->content), "abc=33"))
	{
		printf("last content = '%s'\n", (char *)ft_lstlast(g_env)->content);
		printf("result content = '%s'\n", (char *)(result6->content));
		exit(1);
	}

	ft_lstdel_last(g_env, free);
	free_cmd_struct(cmd_line6);
	free_cmd_struct(cmd_line6_1);
	printf("==============  case6 ok ==============\n");


	char		*case7 = "export abc+=3";

	t_cmd_line	*cmd_line7 = get_command_line(&case7);

	if (export(cmd_line7))
		printf("return ok\n");
	else
		printf("return must be true!!!!!\n");
	
	t_list *result7 = find_env_target_list("abc");
	if (!result7)
	{
		perror("no result\n");
		exit(1);
	}
	if (!are_equal((char *)(result7->content), "abc=3"))
	{
		printf("last content = '%s'\n", ((char *)ft_lstlast(g_env)->content));
		printf("result content = '%s'\n", (char *)(result7->content));
		exit(1);
	}
	ft_lstdel_last(g_env, free);
	free_cmd_struct(cmd_line7);
	printf("==============  case7 ok ==============\n");


	char		*case8 = "export a=1 =b c=2 =d";
	t_cmd_line	*cmd_line8 = get_command_line(&case8);

	if (!export(cmd_line8))
		printf("return ok\n");
	else
		printf("return must be false!!!!!!!!!!!\n");
	
	t_list *expect8 = find_env_target_list("a");
	t_list *expect8_1 = find_env_target_list("c");

	if (!expect8 || !expect8_1)
		perror("not append export\n");
	if (!(are_equal((char *)expect8->content, "a=1")))
		perror("expect8 is fail\n");
	if (!(are_equal((char *)expect8_1->content, "c=2")))
		perror("expect8_1 is fail\n");

	print_err_msg();
	ft_lstdel_last(g_env, free);
	ft_lstdel_last(g_env, free);
	free_cmd_struct(cmd_line8);
	printf("==============  case8 ok ==============\n");



	char		*case9 = "export a+= 1";
	t_cmd_line	*cmd_line9 = get_command_line(&case9);

	if (export(cmd_line9))
		printf("rturn must be fail!!!!!!\n");
	else
		printf("return  ok\n");
	
	t_list *expect9 = find_env_target_list("a");

	if (!expect9)
		perror("not append export\n");
	if (!(are_equal((char *)expect9->content, "a=")))
	{
		printf("err ----- content is '%s'\n", ((char *)expect9->content));
		exit(1);
	}

	print_err_msg();
	ft_lstdel_last(g_env, free);
	free_cmd_struct(cmd_line9);
	printf("==============  case9 ok ==============\n");


	char		*case10 = "export ++";
	t_cmd_line	*cmd_line10 = get_command_line(&case10);

	if (export(cmd_line10))
		printf("rturn must be fail!!!!!!\n");
	else
		printf("return  ok\n");

	print_err_msg();
	free_cmd_struct(cmd_line10);
	printf("==============  case10 ok ==============\n\n");


	char		*case11 = "export a +=1";
	t_cmd_line	*cmd_line11 = get_command_line(&case11);

	if (export(cmd_line11))
		printf("return must be fail!!!!!!\n");
	else
		printf("return  ok\n");

	t_list *target11 = find_env_target_list("a");
	if (target11)
	{
		printf("fail ---- appended target\n\n");
		exit(1);
	}

	print_err_msg();
	free_cmd_struct(cmd_line11);
	printf("==============  case11 ok ==============\n");
}

