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

void test_export(t_list *env)
{
	char 		*case1 = "export a=1";
	char 		*expect1 = "a=1";
	t_cmd_line	*cmd_line1 = get_command_line(&case1, env);

	export(cmd_line1, env, 0);
	t_list *result1 = find_env_target_list(env, "a");
	if (!are_equal(expect1, (char *)(result1->content)))
		message_and_exit((char *)(result1->content), false);
	ft_lstdel_last(env, free);
	free_cmd_struct(cmd_line1);
	free(cmd_line1);
	printf("==============  case1 OK ==============\n");


	char		*case2 = "export a=";
	char		*expect2 = "a=";
	t_cmd_line	*cmd_line2 = get_command_line(&case2, env);

	export(cmd_line2, env, 0);
	t_list *result2 = find_env_target_list(env, "a");
	if (!are_equal(expect2, result2->content))
		message_and_exit(result2->content, false);
	ft_lstdel_last(env, free);
	free_cmd_struct(cmd_line2);
	free(cmd_line2);
	printf("==============  case2 OK ==============\n");


	char		*case3 = "export a=1 c b=2";
	char		*expect3 = "a=1";
	char		*expect3_1 = "b=2";
	t_cmd_line	*cmd_line3 = get_command_line(&case3, env);

	export(cmd_line3, env, 0);
	t_list *result3 = find_env_target_list(env, "a");
	t_list *result3_1 = find_env_target_list(env, "b");

	if (!are_equal(expect3, result3->content))
		message_and_exit(result3->content, false);
	if (!are_equal(expect3_1, result3_1->content))
		message_and_exit(result3_1->content, false);
	ft_lstdel_last(env, free);
	ft_lstdel_last(env, free);
	free_cmd_struct(cmd_line3);
	free(cmd_line3);
	printf("==============  case3 OK ==============\n");



	char		*case4 = "export =";
	char		*expect4 = 0;
	t_cmd_line	*cmd_line4 = get_command_line(&case4, env);

	t_list *before_last = ft_lstlast(env);
	export(cmd_line4, env, 0);
	
	if (before_last != ft_lstlast(env))
		exit(1);
	print_err_msg();

	free_cmd_struct(cmd_line4);
	free(cmd_line4);
	printf("==============  case4 ok ==============\n");


	char		*case5 = "export abc@=3";
	t_cmd_line	*cmd_line5 = get_command_line(&case5, env);

	t_list *before_last5 = ft_lstlast(env);
	export(cmd_line5, env, 0);
	
	if (before_last5 != ft_lstlast(env))
	{
		printf("last content = %s\n", (char *)ft_lstlast(env)->content);
		exit(1);
	}
	print_err_msg();

	free_cmd_struct(cmd_line5);
	free(cmd_line5);
	printf("==============  case5 ok ==============\n");
}

