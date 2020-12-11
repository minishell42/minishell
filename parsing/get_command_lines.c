#include "parsing.h"

static int	set_command_line(t_cmd_line *cmd_line, char *line, char *quot_flag, t_list *env)
{
	char			*start;
	int				len;
	int				index;
	int				tmp_index;
	int				flag;
	
	index = 0;
	tmp_index = 0;
	start = line;
	while (line[index])
	{
		check_chacter_in_line(line, &index, quot_flag, ft_isspace);
		if (*quot_flag)
			return (QUOT_IS_NOT_PAIR);
		len = (line + index) - start;
		if (!line[index + 1])
			len++;
		if ((flag = parse_command(cmd_line, start, len, env)) <= 0)
		{
			if (flag < 0)
				return (INVALID_COMMAND);
			index = tmp_index;
			break;
		}
		while (line[index] == ' ' && line[index + 1] == ' ')
			index++;
		index++;
		start = line + index;
		tmp_index = index;
	}
	index += set_param(cmd_line, start, env); // 8 + param 의 길이 
	return (index);
}

t_cmd_line	*get_command_line(char **line_ptr, char *quot_flag, t_list *env)
{	
	t_cmd_line		*command_line;
	int				index;
	char			*line;

	line = ft_strtrim(*line_ptr, " ");  // 메모리 누수 가능성
	if (!(command_line = ft_calloc(sizeof(t_cmd_line), 1)))
	{
		*quot_flag = MALLOC_ERROR;
		return (NULL);
	}
	index = set_command_line(command_line, line, quot_flag, env);
	if (index < 0)
	{
		*quot_flag = index;
		return (NULL);
	}
	check_redirection(command_line);
	change_param_value(command_line, env);
	*line_ptr = line + index;
	return (command_line);
}

void	print_err_msg(char error_flag)
{
	if (error_flag == MALLOC_ERROR)
		write(1, "malloc error\n", 14);
	else if (error_flag == QUOT_IS_NOT_PAIR)
		write(1, "quotation mark is not pair\n", 28);
	else if (error_flag == INVALID_COMMAND)
		write(1, "invalid command\n", 17);
}

t_list	*get_command_lines(char *line, t_list *env)
{
	t_list			*list;
	t_cmd_line		*command_line;
	char			quot_flag;

	list = 0;
	quot_flag = 0;
	while (line && *line)
	{
		if (!(command_line = get_command_line(&line, &quot_flag, env)))
		{
			if (quot_flag)
				print_err_msg(quot_flag);
			return (NULL);
		}
		if (!list)
			list = ft_lstnew(command_line);
		else
			ft_lstadd_back(&list, ft_lstnew(command_line));
	}
	return (list);
}
