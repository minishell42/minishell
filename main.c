#include "minishell.h"

// int			get_command_num(char *command)
// {
//     if (are_equal(command, "echo"))
// 	{
// 		return (ECHO);
// 	}
// 	// exit?
// 	return (0);
// }


// // bool		is_option(char *str)
// // {
	

// // }

// bool		set_option(t_cmd_line *cmd_line, char **splited_line)
// {
// 	int			count;
// 	char		*option;

// 	count = 0;
// 	while (splited_line[count])
// 		count++;
// 	// is_option(splited_line[1]);
// 	return (true);
// }

// void		echo(t_cmd_line *cmd_line, char *envp[])
// {
// 	int			pid;
// 	int			status;
	
// 	pid  = fork();
// 	if (pid > 0)
// 		waitpid(pid, NULL, 0);
// 	else if (pid == 0)
// 		execve("/usr/bin/lessecho", &cmd_line->param, envp);
// 	else
// 		exit(0);	
// }

// void		excute(t_cmd_line *cmd_line, char *envp[])
// {
// 	if (cmd_line->command_num == ECHO)
// 		echo(cmd_line, envp);
// }

// // char		*get_str_in_quotation_set(char *str)
// // {
	
// // }
// char		*get_param(char *start)
// {
// 	char	*param;
// 	int		param_len;

// 	param_len = ft_strlen(start) + 1;
// 	param = ft_calloc(sizeof(char), param_len);
// 	ft_strlcpy(param, start, param_len);
// 	return (param);
// }

// t_cmd_line	*get_command_line(char **line_ptr)
// {	
// 	t_cmd_line		*command_line;
// 	int				i;
// 	bool			quotation_flag;
// 	char			*start;
// 	char			*value;
// 	char			*line;
// 	int				len;

// 	line = ft_strtrim(*line_ptr, " ");
// 	printf("line = %s\n", line);
// 	quotation_flag = false;
// 	command_line = ft_calloc(sizeof(t_cmd_line), 1);
// 	i = 0;
// 	start = line;
// 	while (line[i])
// 	{
// 		if (line[i] == ' ' || !line[i + 1])
// 		{
// 			len = (line + i) - start;
// 			if (!line[i + 1])
// 				len++;
// 			value = ft_calloc(sizeof(char), len + 1);
// 			ft_strlcpy(value, start, len + 1);
// 			if (!command_line->command)
// 			{
// 				command_line->command = value;
// 				command_line->command_num = get_command_num(command_line->command);
// 				// !command_line->command_num 에러처리
// 			}
// 			else if (command_line->command_num == ECHO && are_equal(value, "-n"))
// 			{
// 				if (!command_line->option)
// 					command_line->option = value;
// 				else
// 					free(value);
// 			}
// 			else
// 			{
// 				free(value);
// 				break;
// 			}
// 				// 나머지를 전부 param으로 넣어준다.
// 				/* 심화
// 					일단 쭉가면서 redirection, pipe, semi colon이 나오는지 확인하고
// 					나오지 않는다면 모두 pram으로 넣어준다

// 					나온다면 나온 문자열 전까지 저장하고 브레이크 
// 				*/
// 			while (line[i] == ' ' && line[i + 1] == ' ')
// 				i++;
// 			start = line + i + 1;
// 		}
// 		i++;
// 	}
// 	// value = ft_calloc(sizeof(char), ft_strlen(start) + 1);
// 	// ft_strlcpy(value, start, ft_strlen(start) + 1);
// 	command_line->param = get_param(start);
// 	// printf("value = %s, len = %ld\n start = %c\n", value, ft_strlen(value), *start);
// 	// command_line->param = value;
// 	i += ft_strlen(command_line->param);
// 	*line_ptr = line + i;
// 	return (command_line);
// }

// t_list	*get_command_lines(char *line)
// {
// 	t_list			*list;
// 	t_cmd_line		*command_line;
// 	// char			*tmp;

// 	list = ft_calloc(sizeof(t_list), 1);
// 	// tmp = ft_calloc(sizeof(char), ft_strlen(line));
// 	while (line)
// 	{
// 		// 일단 ; 상관없이 command_line이 하나만 있다고 생각.
// 		// command_line = set_command_line(line);

// 		// ft_lstadd_back(&list, command_line);
// 	}
// 	return (list);
// }


int			main(int argc, char **argv, char *envp[])
{
	char		*line;
	t_list		*command_lines;

	while (true)
	{
		write(1, "minishell$ ", 12);
		get_next_line(0, &line);
		// command_lines = get_command_lines(line);
		t_cmd_line *cmd_line = get_command_line(&line);
		printf("command = %s, option = %s, param = %s\n", cmd_line->command, cmd_line->option, cmd_line->param);
	}
	return (0);
}
