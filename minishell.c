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
	// 1 fork child
	while (line && *line)
	{
		// echo 123 > 123 | echo 345 -> pipe flag, redir flag -> fork 2번
		// echo 123 > 123 ; echo 345
		// main basic
		//		minishell child  	pipe
		//				child		pipe
		//					value write pipe
		//				child exit()
		//		minishell read pipe
		//				redir
		//		minishell
		//				child
		//			redir->child
		if (!(command_line = get_command_line(&line, env)))
		{
			// 따옴표 에러
			if (g_err.err_number)
				print_err_msg();
			return ;
		}
		// cmd_line = echo 123 > 123
		// if pipe flag on -> 2 fork -> parent ->wait
		// 2 fork child -> check redirection
		if (are_equal(command_line->command, "a"))
		{
			while (42)
				printf("err\n");
		}
		// if redirection 3 fork ex) echo 123 > 123; 3 fork parent -> run command
		// 3 fork child -> redirection
		// pipe 3 fork parent child combine
		res = run_command(command_line, env);
		redirection(command_line, env, res); // bool type
		free(res);
		free_cmd_struct(command_line);
		free(command_line);
	}
}
