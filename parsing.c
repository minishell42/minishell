#include "minishell.h"

int			get_command_num(char *command)
{
    if (are_equal(command, "echo"))
	{
		return (ECHO);
	}
	// exit?
	return (0);
}


// bool		is_option(char *str)
// {
	

// }

bool		set_option(t_cmd_line *cmd_line, char **splited_line)
{
	int			count;
	char		*option;

	count = 0;
	while (splited_line[count])
		count++;
	// is_option(splited_line[1]);
	return (true);
}

void		echo(t_cmd_line *cmd_line, char *envp[])
{
	int			pid;
	int			status;
	
	pid  = fork();
	if (pid > 0)
		waitpid(pid, NULL, 0);
	else if (pid == 0)
		execve("/usr/bin/lessecho", &cmd_line->param, envp);
	else
		exit(0);	
}

void		excute(t_cmd_line *cmd_line, char *envp[])
{
	if (cmd_line->command_num == ECHO)
		echo(cmd_line, envp);
}

// char		*get_str_in_quotation_set(char *str)
// {
	
// }
char		*get_param(char *start)
{
	char	*param;
	int		param_len;

	param_len = ft_strlen(start) + 1;
	param = ft_calloc(sizeof(char), param_len);
	ft_strlcpy(param, start, param_len);
	return (param);
}

void		remove_quotation(char *value)
{
	char	quot_flag;
	int		index;

	quot_flag = 0;
	while (value && *value)
	{
		index = 0;
		while (*value && *value != '"' && *value != '\'')
			value++;
		if (*value == '"' || *value == '\'')
		{
			if (quot_flag == 0)
				quot_flag = *value;
			else if (quot_flag == *value)
				quot_flag = 0;
		}
		if (quot_flag == *value || quot_flag == 0)
			while (value && value[index++])
				value[index - 1] = value[index];
		else
			value++;
	}
}

bool		parse_cmd_line(t_cmd_line *cmd_line, char *start, int len)
{
	char	*value;

	value = ft_calloc(sizeof(char), len + 1);
	ft_strlcpy(value, start, len + 1);
	remove_quotation(value);
	if (!cmd_line->command)
	{
		cmd_line->command = value;
		cmd_line->command_num = get_command_num(cmd_line->command);
		// !cmd_line->command_num 에러처리
		return (true);
	}
	else if (cmd_line->command_num == ECHO && are_equal(value, "-n"))
	{
		if (!cmd_line->option)
			cmd_line->option = value;
		else
			free(value);
		return (true);
	}
	free(value);
	return (false);
}
// 우리가 하고 싶은 것
// 공백을 기준으로 cmd_line에 들어갈 값들을 분리
// but 공백은 따옴표 안에 속하지 않는 공백만 인정
void		check_quotation_in_line(char *line, int *index, char *quot_flag)
{
	while (line[*index] && !(ft_isspace(line[*index]) && *quot_flag == 0))
	{
		if (line[*index] == '\'' || line[*index] == '"')
		{
			if (*quot_flag == line[*index])
				*quot_flag = 0;
			else if (*quot_flag == 0)
				*quot_flag = line[*index];
		}
		(*index)++;
	}

}

t_cmd_line	*get_command_line(char **line_ptr, char *quot_flag)
{	
	t_cmd_line		*command_line;
	int				index;
	char			*start;
	char			*line;
	int				len;

//  echo ";"; echo 123
	line = ft_strtrim(*line_ptr, " ");
	command_line = ft_calloc(sizeof(t_cmd_line), 1);
	index = 0;
	start = line;
	while (line[index])
	{
		// 현재 문자가 공백이고 플래그가 서있지 않을 경우 저장
		// 저장한 문자열을 적절한 cmd_line 필드에 분배
		// if (line[index] == ' ' || !line[index + 1])
		// {
		// 	len = (line + index) - start;
		// 	if (!line[index + 1])
		// 		len++;
		// 	if (!parse_cmd_line(command_line, start, len))
		// 		break;
		// 	while (line[index] == ' ' && line[index + 1] == ' ')
		// 		index++;
		// 	start = line + index + 1;
		// }
		// index++;
		// printf("line : %c\nindex : %d\nquot_flag : %c\n", *line, index, *quot_flag);
		check_quotation_in_line(line, &index, quot_flag);
		// printf("line2 : %c\nindex2 : %d\nquot_flag2 : %c\n", *line, index, *quot_flag);
		if (*quot_flag)
			return (NULL);
		len = (line + index) - start;
		if (!line[index + 1])
			len++;
		if (!parse_cmd_line(command_line, start, len))
			break;
		while (line[index] == ' ' && line[index + 1] == ' ')
			index++;
		index++;
		start = line + index;
		// printf("end of while\n");
	}
	// " " flag가 서지 않는 상태에서 ;를 만나면 ;을 널문자로 변경시키고 그 전까지의 값을 param으로 입력하고, line의 주소값을 ;다음의 주소값으로 민다.
	command_line->param = get_param(start);
	index += ft_strlen(command_line->param);
	*line_ptr = line + index;
	return (command_line);
}

t_list	*get_command_lines(char *line)
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
		if (!(command_line = get_command_line(&line, &quot_flag)))
		{
			if (quot_flag)
				write(1, "quotation mark is not pair\n", 28);
			return (NULL);
		}
		// 일단 ; 상관없이 command_line이 하나만 있다고 생각.
		// command_line = set_command_line(line);

		// ft_lstadd_back(&list, command_line);
	}
	return (list);
}
