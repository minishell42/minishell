#include "test.h"

// bool	is_valid_key(char *env_key)
// {
// 	int		i;

// 	i = 0;
// 	if (ft_isdigit(*env_key))
// 		return (false);
// 	while (env_key[i] && env_key[i] != '=')
// 	{
// 		if (is_contained(env_key[i], "!@#$%^&*()_+."))
// 			return (false);
// 		i++;
// 	}
// 	return (true);
// }

// // bool	validate_env_key(char *env_key)
// // {
// // 	int		i;

// // 	i = 0;
// // 	if (!env_key)
// // 		return (true);
// // 	if (!(*env_key))
// // 		return (false);
// // 	return (is_valid_key(env_key));
// // }

// t_list *get_valid_param(t_list *param)
// {
// 	t_list *valid_params;

// 	valid_params = NULL;
// 	while (param)
// 	{
// 		if (is_valid_key(param->content))
// 		{
// 			if (valid_params)
// 				ft_lstadd_back(&valid_params, ft_lstnew(ft_strdup(param->content)));
// 			else
// 				valid_params = ft_lstnew(ft_strdup(param->content));
// 		}
// 		else
// 			make_err_msg("unset", param->content, get_err_msg(INVALID_EXPORT_PARAM));
// 		param = param->next;
// 	}
// 	return (valid_params);
// }

// void	check_and_remove_env_value(t_list *param, char *key,
// 									t_list **env, t_list *prev_env)
// {
// 	// printf("what is key ? '%s'\n", key);
// 	while (param)
// 	{
// 		// printf("loop\n");
// 		if (are_equal(param->content, key))
// 		{
// 			printf("remove params content ? '%s'\n", (char *)param->content);
// 			prev_env->next = (*env)->next;
// 			ft_lstdelone(*env, free);
// 			*env = NULL;
// 			return  ;
// 		}
// 		param = param->next;
// 	}
// }

// // void	print_struct(t_list *list)
// // {
// // 	int	i;

// //	i = 1;
// // 	while (list)
// // 	{
// // 		printf("list content : index ? %d\tcontent ? '%s'\n", i, (char *)list->content);
// //		list = list->next;
// //		i++;
// // 	}
// // }

// bool	ft_unset(t_cmd_line *cmd_line)
// {
// 	t_list	*params;
// 	int		i;
// 	t_list	*env;
// 	t_list	*prev;
// 	char	*key;

// 	env = g_env;
// 	if (!(params = get_valid_param(cmd_line->param)))
// 		return (false);
// 	prev = env;
// 	while (env)
// 	{
// 		i = 0;
// 		while ((((char *)env->content)[i] != '=') && ((char *)env->content)[i])
// 			i++;
// 		key = ft_substr(env->content, 0, i);
// 		check_and_remove_env_value(params, key, &env, prev);
// 		free(key);
// 		if (!env && prev != g_env)
// 			env = prev->next;
// 		else
// 		{
// 			prev = env;
// 			env = env->next;	
// 		}
// 		i++;
// 	}
// 	ft_lstclear(&params, free);
// 	if (g_err)
// 		return (false);
// 	return (true);
// }

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
	char *line3_1 = ft_strdup("b=1");ist *list)
// {
// 	int	i;

//	i = 1;
// 	while (list)
// 	{
// 		printf("list content : index ? %d\tcontent ? '%s'\n", i, (char *)list->content);
//		list = list->next;
//		i++;
// 	}
// }
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
	// char *line4 = "unset b a=1 test2 cd+";
	// t_cmd_line *cmd_line4 = get_command_line(&line4);
	// char *line4_1 = ft_strdup("b=12");
	// char *line4_2 = ft_strdup("test2=1234");
	// ft_lstadd_back(&g_env, ft_lstnew(line4_1));
	// ft_lstadd_back(&g_env, ft_lstnew(line4_2));
	// target = find_env_target_list("test2");
	// if (!target)
	// {
	// 	printf("not added target\n");
	// 	exit(1);
	// }
	// printf("added target content = '%s'\n", ((char *)target->content));
	// target = find_env_target_list("b");
	// if (!target)
	// {
	// 	printf("not added target\n");
	// 	exit(1);
	// }
	// printf("added target content = '%s'\n", ((char *)target->content));
	// if (!ft_unset(cmd_line4))
	// 	built_in_error();
	// after_target = find_env_target_list("test2");
	// if (after_target)
	// {
	// 	printf("after unset :: not delete param : '%s'\n", (char *)after_target->content);
	// 	exit(1);
	// }
	// after_target = find_env_target_list("b");
	// if (after_target)
	// {
	// 	printf("after unset :: not delete param : '%s'\n", (char *)after_target->content);
	// 	exit(1);
	// }
	// free_cmd_struct(cmd_line4);
	// printf("=========================== case4 ok ===========================\n");