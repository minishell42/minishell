#include "test.h"

// void	print_content(void *content)
// {
// 	int		len;
// 	char	*str;

// 	if (!content)
// 		return ;
// 	str = content;
// 	len = ft_strlen(content);
// 	str[len] = '\n';
// 	write(1, str, len + 1);
// 	str[len] = '\0';
// }

t_list	*ft_lstcpy(t_list *list)
{
	t_list *ret;

	if (!list)
		return (NULL);
	ret = ft_lstnew(ft_strdup(list->content));
	list = list->next;
	while (list)
	{
		ft_lstadd_back(&ret, ft_lstnew(ft_strdup(list->content)));
		list = list->next;
	}
	return (ret);
}


// param 값에 '='이 포함 되는지 확인
// 포함된다면 copy한 env에 add back
// 포함되지 않는다면 명령어로 인식

// 명령어가 있다면 copy를 전달해서 실행
// 명령어가 없다면 copy의 contents를 출력

// env test=1 tes=2 cat 123 
// param_list : cat
// new cmd_line->command = param_list->content
// param_list = param_list->next
// cmd_line->param = param_list

// bool	ft_env(t_cmd_line *cmd_line)
// {
// 	t_list		*param;
// 	char		*param_str;
// 	char		*tmp;
// 	t_cmd_line	*env_cmd_line;

// 	param = cmd_line->param;
// 	while (param)
// 	{
// 		if (ft_strchr(param->content, '='))
// 			ft_lstadd_back(&g_env, ft_lstnew(ft_strdup(param->content)));
// 		else
// 			break ;
// 		param = param->next;
// 	}
// 	if (param)
// 	{
// 		param_str = make_param_str(param);
// 		tmp = param_str;
// 		if (!(env_cmd_line = get_command_line(&param_str)))
// 		{
// 			free(tmp);
// 			return (false);
// 		}
// 		if (!run_command(env_cmd_line))
// 		{
// 			free_cmd_struct(env_cmd_line);
// 			free(tmp);
// 			return (false);
// 		}
// 		free_cmd_struct(env_cmd_line);
// 		free(tmp);
// 	}
// 	else
// 		ft_lstiter(g_env, print_content);
// 	return (true);
// }

void test_env()
{
	char *line1 = "env";
	t_cmd_line *cmd_line1 = get_command_line(&line1);
	ft_env(cmd_line1);
	free_cmd_struct(cmd_line1);

	printf("==================  line1 OK  =======================\n");

	char *line2 = "env a=1";
	t_cmd_line *cmd_line2 = get_command_line(&line2);
	ft_env(cmd_line2);
	ft_lstdel_last(g_env, free);

	free_cmd_struct(cmd_line2);

	printf("==================  line2 OK  =======================\n");
	
	char *line3 = "env a=1 b=2";
	t_cmd_line *cmd_line3 = get_command_line(&line3);
	ft_env(cmd_line3);
	ft_lstdel_last(g_env, free);
	ft_lstdel_last(g_env, free);
	free_cmd_struct(cmd_line3);

	printf("==================  line3 OK  =======================\n");

	char *line4 = "env echo 123";
	t_cmd_line *cmd_line4 = get_command_line(&line4);
	ft_env(cmd_line4);
	free_cmd_struct(cmd_line4);

	printf("==================  line4 OK  =======================\n");

	char *line5 = "env a=1 echo 1234";
	t_cmd_line *cmd_line5 = get_command_line(&line5);
	
	ft_env(cmd_line5);
	ft_lstdel_last(g_env, free);
	free_cmd_struct(cmd_line5);

	printf("==================  line5 OK  =======================\n");

	char *line6 = "env a+=1 b c=1 echo 1234";
	t_cmd_line *cmd_line6 = get_command_line(&line6);
	if (ft_env(cmd_line6))
	{
		printf("retern must be false!!!!!!!\n");
		exit(1);
	}
	else
		built_in_error();
	ft_lstdel_last(g_env, free);
	free_cmd_struct(cmd_line6);

	printf("==================  line6 OK  =======================\n");

	// char *line6 = "env a+=1 b c=1 echo 1234";
	// t_cmd_line *cmd_line6 = get_command_line(&line6);
	// if (ft_env(cmd_line6))
	// {
	// 	printf("retern must be false!!!!!!!\n");
	// 	exit(1);
	// }
	// else
	// 	built_in_error();
	// ft_lstdel_last(g_env, free);
	// free_cmd_struct(cmd_line6);

	// printf("==================  line6 OK  =======================\n");

}