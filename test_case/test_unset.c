#include "test.h"

void test_unset()
{
	char *line1 = "unset a";
	t_cmd_line *cmd_line1 = get_command_line(&line1);

	ft_lstadd_back(&g_env, ft_lstnew(ft_strdup("a=1")));
	t_list *target = find_env_target_list("a");

	if (!target)
	{
		printf("not added target\n");
		exit(1);
	}
	printf("added target content = '%s'\n", ((char *)target->content));
	
	ft_unset(cmd_line1);
	t_list *after_target = find_env_target_list("a");
	if (after_target)
	{
		printf("fail unset\n");
		exit(1);
	}
	free_cmd_struct(cmd_line1);
	printf("=========================== case1 ok ===========================\n");


	char *line2 = "unset b";
	t_cmd_line *cmd_line2 = get_command_line(&line2);
	char *line2_1 = ft_strdup("b=1");
	char *line2_2 = ft_strdup("test=123");
	ft_lstadd_back(&g_env, ft_lstnew(line2_1));
	ft_lstadd_back(&g_env, ft_lstnew(line2_2));
	target = find_env_target_list("test");
	if (!target)
	{
		printf("not added target\n");
		exit(1);
	}
	printf("added target content = '%s'\n", ((char *)target->content));
	target = find_env_target_list("b");
	if (!target)
	{
		printf("not added target\n");
		exit(1);
	}
	printf("added target content = '%s'\n", ((char *)target->content));
	ft_unset(cmd_line2);
	after_target = find_env_target_list("test");
	if (after_target)
		printf("after unset :: not delete param : '%s'\n", (char *)after_target->content);
	after_target = find_env_target_list("b");
	if (after_target)
	{
		printf("after unset :: not delete param : '%s'\n", (char *)after_target->content);
		exit(1);
	}
	free_cmd_struct(cmd_line2);
	printf("=========================== case2 ok ===========================\n");

	char *line3 = "unset b test2";
	t_cmd_line *cmd_line3 = get_command_line(&line3);
	char *line3_1 = ft_strdup("b=1");
	char *line3_2 = ft_strdup("test2=2");
	ft_lstadd_back(&g_env, ft_lstnew(line3_1));
	ft_lstadd_back(&g_env, ft_lstnew(line3_2));

	target = find_env_target_list("test2");
	if (!target)
	{
		printf("not added target\n");
		exit(1);
	}
	printf("added target content = '%s'\n", ((char *)target->content));
	target = find_env_target_list("b");
	if (!target)
	{
		printf("not added target\n");
		exit(1);
	}
	printf("added target content = '%s'\n", ((char *)target->content));
	ft_unset(cmd_line3);
	after_target = find_env_target_list("test2");
	if (after_target)
	{
		printf("after unset :: not delete param : '%s'\n", (char *)after_target->content);
		exit(1);
	}
	after_target = find_env_target_list("b");
	if (after_target)
	{
		printf("after unset :: not delete param : '%s'\n", (char *)after_target->content);
		exit(1);
	}
	free_cmd_struct(cmd_line3);
	printf("=========================== case3 ok ===========================\n");

	char *line4 = "unset b 1 test2 cd+";
	t_cmd_line *cmd_line4 = get_command_line(&line4);
	char *line4_1 = ft_strdup("b=12");
	char *line4_2 = ft_strdup("test2=1234");
	ft_lstadd_back(&g_env, ft_lstnew(line4_1));
	ft_lstadd_back(&g_env, ft_lstnew(line4_2));
	target = find_env_target_list("test2");
	if (!target)
	{
		printf("not added target\n");
		exit(1);
	}
	printf("added target content = '%s'\n", ((char *)target->content));
	target = find_env_target_list("b");
	if (!target)
	{
		printf("not added target\n");
		exit(1);
	}
	printf("added target content = '%s'\n", ((char *)target->content));
	if (!(ft_unset(cmd_line4)))
		built_in_error();	
	after_target = find_env_target_list("test2");
	if (after_target)
	{
		printf("after unset :: not delete param : '%s'\n", (char *)after_target->content);
		exit(1);
	}
	after_target = find_env_target_list("b");
	if (after_target)
	{
		printf("after unset :: not delete param : '%s'\n", (char *)after_target->content);
		exit(1);
	}
	free_cmd_struct(cmd_line4);
	printf("=========================== case4 ok ===========================\n");
	
}
