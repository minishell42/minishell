#include "minishell.h"

void	minishell(char *line, t_list *env)
{
	t_cmd_line		*command_line;
	char			*res;

	g_err.err_number = 0;
	g_err.err_value = 0;
	signal(SIGINT, child_exit);
	signal(SIGQUIT, child_exit);
	if (!validate_line(line))
	{
		printf("errnum = %d\n", g_err.err_number);
		if (g_err.err_number)
			print_err_msg();
		return ;
	}
	while (line && *line)
	{
		if (!(command_line = get_command_line(&line, env)))
		{
			// 따옴표 에러
			if (g_err.err_number)
				print_err_msg();
			return ;
		}
		// if (are_equal(command_line->command, "a"))
		// {
		// 	while (42)
		// 		printf("err\n");
		// }
		res = run_command(command_line, env);
		redirection(command_line, env, res); // bool type
		free(res);
		free_cmd_struct(command_line);
		free(command_line);
		// run_redirection(res, command_line, env);
		// if (g_err.err_number)
			// print_err_msg();
		// flag -> pipe 있다는 것이고 -> 다음 command_line 이용해서 --- run 
		// res = run(command_line, res, env);
		// execve()
		// command_line.pipe_flag가 있으면 -> flag on
		// if (!list)
		// 	list = ft_lstnew(command_line);
		// else
		// 	ft_lstadd_back(&list, ft_lstnew(command_line));
	}
}

// t_list	*get_command_lines(char *line, t_list *env)
// {
// 	t_list			*list;
// 	t_cmd_line		*command_line;

// 	list = NULL;
// 	g_err.err_number = 0;
// 	g_err.err_value = 0;
// 	while (line && *line)
// 	{
// 		printf("loop\n");
// 		if (!(command_line = get_command_line(&line, env)))
// 		{
// 			if (g_err.err_number)
// 				print_err_msg();
// 			break;
// 		}
// 		// flag -> pipe 있다는 것이고 -> 다음 command_line 이용해서 --- run 
// 		// res = run(command_line, res, env);
// 		// execve()
// 		// command_line.pipe_flag가 있으면 -> flag on
// 		if (!list)
// 			list = ft_lstnew(command_line);
// 		else
// 			ft_lstadd_back(&list, ft_lstnew(command_line));
// 	}
// 	return (list);
// }
