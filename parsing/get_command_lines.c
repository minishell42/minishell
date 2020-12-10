#include "parsing.h"

t_cmd_line	*get_command_line(char **line_ptr, char *quot_flag, t_list *env)
{	
	t_cmd_line		*command_line;
	int				index;
	char			*start;
	char			*line;
	int				len;

//  echo ";"; echo 123
	line = ft_strtrim(*line_ptr, " ");  // 메모리 누수 가능성 
	command_line = ft_calloc(sizeof(t_cmd_line), 1);
	index = 0;
	start = line;
	while (line[index])
	{
		// 현재 문자가 공백이고 플래그가 서있지 않을 경우 저장
		// 저장한 문자열을 적절한 cmd_line 필드에 분배
		// printf("line : %c\nindex : %d\nquot_flag : %c\n", *line, index, *quot_flag);
		// check_quotation_in_line(line, &index, quot_flag);
		check_chacter_in_line(line, &index, quot_flag, ft_isspace);
		// printf("line2 : %c\nindex2 : %d\nquot_flag2 : %c\n", *line, index, *quot_flag);
		if (*quot_flag)
			return (NULL);
		len = (line + index) - start;
		// printf("i")
		if (!line[index + 1])
			len++;
		if (!parse_cmd_line(command_line, start, len, env))
			break;
		while (line[index] == ' ' && line[index + 1] == ' ')
			index++;
		index++;
		start = line + index;
		// printf("end of while\n");
	}
	// " " flag가 서지 않는 상태에서 ;를 만나면 ;을 널문자로 변경시키고 그 전까지의 값을 param으로 입력하고, line의 주소값을 ;다음의 주소값으로 민다.

	printf("before set_param\n");
	set_param(command_line, start);
	index += ft_strlen(command_line->param);
	check_redirection(command_line);
	printf("param = %s\n", command_line->param);
	if (command_line->redir_flag)
		set_redirection_param(command_line);
	else
	{
		// command_line->param free해야 함
		printf("before set_multi_env\n");
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
	// char			*tmp;

	list = ft_calloc(sizeof(t_list), 1);
	quot_flag = 0;
	// tmp = ft_calloc(sizeof(char), ft_strlen(line));
	while (line)
	{
		if (!(command_line = get_command_line(&line, &quot_flag, env)))
		{
			if (quot_flag)
				write(1, "quotation mark is not pair\n", 28);
			return (NULL);
		}
		// 일단 ; 상관없이 command_line이 하나만 있다고 생각.
		// command_line = set_command_line(line);
		if (!list)
			list = ft_lstnew(command_line);
		else
			ft_lstadd_back(&list, ft_lstnew(command_line));
	}
	return (list);
}