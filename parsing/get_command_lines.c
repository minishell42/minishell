#include "parsing.h"

t_cmd_line	*get_command_line(char **line_ptr, char *quot_flag, t_list *env)
{	
	t_cmd_line		*command_line;
	int				index;
	char			*start;
	char			*line;
	int				len;

	line = ft_strtrim(*line_ptr, " ");  // 메모리 누수 가능성 
	command_line = ft_calloc(sizeof(t_cmd_line), 1);
	index = 0;
	start = line;
	while (line[index])
	{
		check_chacter_in_line(line, &index, quot_flag, ft_isspace);
		if (*quot_flag)
			return (NULL);
		len = (line + index) - start;
		if (!line[index + 1])
			len++;
		if (!parse_cmd_line(command_line, start, len, env))
			break;
		while (line[index] == ' ' && line[index + 1] == ' ')
			index++;
		index++;
		start = line + index;
	}
	set_param(command_line, start);
	index += ft_strlen(command_line->param);
	check_redirection(command_line);
	if (command_line->redir_flag)
		set_redirection_param(command_line);
	else
	{
		command_line->param = set_multi_env(command_line->param, env); // 메모리 누수 가능성 : parameter : command_line
		remove_quotation(command_line->param);
		command_line->param = ft_strtrim(command_line->param, " "); // 메모리 누수 가능성
	}
	*line_ptr = line + index;
	return (command_line);
}

t_list	*get_command_lines(char *line, t_list *env)
{
	t_list			*list;
	t_cmd_line		*command_line;
	char			quot_flag;

	list = ft_calloc(sizeof(t_list), 1);
	quot_flag = 0;
	while (line)
	{
		if (!(command_line = get_command_line(&line, &quot_flag, env)))
		{
			if (quot_flag)
				write(1, "quotation mark is not pair\n", 28);
			return (NULL);
		}
		if (!list)
			list = ft_lstnew(command_line);
		else
			ft_lstadd_back(&list, ft_lstnew(command_line));
	}
	return (list);
}
