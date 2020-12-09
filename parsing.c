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

int	is_semicolon(int c)
{
	if (c == ';')
	{
		printf("%c\n", c);
		return (true);
	}
	return (false);
}

// int	is_redirection(char *line, int index)
// {
// 	if (line[index] == '<')
// 	{
		
// 	}
// 	return (false);
// }

// line | line | ; line 

// cmd line   ; cmd_line

// cmd p >> file ; cmd_line
// echo 123 >> main.c -> cmd / param / redirection flag / file
// > redirection_out  out_override
// < redirection_     redir_in
// >> redirection_out out_endline
// 구조체에 추가해야 되는 목록
// 1. pipe flag(bool) / 2. redir flag(int) / 3. redir file(char *)
// 헤더파일에 추가해야되는 목록
// define out_override 1 / define redir_in 2 / define out_endline 3

int			is_redirection(int c)
{
	if (c == '<' || c == '>')
		return (true);
	return (false);
}
void		check_chacter_in_line(char *line, int *index, char *quot_flag, int (*func)())
{
	while (line[*index] && !(func(line[*index]) && *quot_flag == 0))
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

// void		check_semi_in_line(char *line, int *index, char *quot_flag)
// {
// 	while (line[*index] && !(is_semicolon(line[*index]) && *quot_flag == 0))
// 	{
// 		if (line[*index] == '\'' || line[*index] == '"')
// 		{
// 			if (*quot_flag == line[*index])
// 				*quot_flag = 0;
// 			else if (*quot_flag == 0)
// 				*quot_flag = line[*index];
// 		}
// 		(*index)++;
// 	}
// }

void		set_env(char **str, t_list *env)
{
	char	*key;
	char	*value;
	char	**key_value;

	if (!str || !str[0] || !ft_strchr(*str, '$'))
		return ;
	str++;
	while (env)
	{
		key_value = ft_split((char *)env->content, "=");
		key = key_value[0];
		value = key_value[1];
		if (are_equal(str, key))
		{
			free(key);
			free(key_value);
			free(*str);
			*str = value;
			return ;
		}
		env = env->next;
	}
	free(key_value);
	free(key);
	free(value);
}

// 문자열 끝에 | 와 ;을 구분하기 힘듬
// -> pipe flag를 통해서 문자열 마지막에 |가 있으면 오류가 발생하게 만들 수 있다.
int			is_separator(int c)
{
	if (c == ';' || c == '|')
		return (true);
	return (false);
}

void		set_param(t_cmd_line *command_line, char *start)
{
	char	*param;
	int		param_len;
	char	flag;
	int		i;

	i = 0;
	flag = 0;
	check_chacter_in_line(start, &i, &flag, is_separator);
	if (start[i] == '|')
		command_line->pipe_flag = true;
	param_len = i + 1;
	param = ft_calloc(sizeof(char), param_len);
	ft_strlcpy(param, start, param_len);
	command_line->param = ft_strtrim(param, " ");
	free(param);
}

void	set_redirection_flag(t_cmd_line *cmd_line, int *i)
{
	char *param;

	param = cmd_line->param;
	if ((param[*i] == '>' || param[*i] == '>') 
		&& (*i != 0 && param[*i - 1] != ' '))
	{
		cmd_line->param[0] = '\0';
		return ;
	}
	if (param[*i] == '>')
	{
		cmd_line->redir_flag = OUT_OVERRIDE;
		if (param[++(*i)] == '>')
		{
			cmd_line->redir_flag = OUT_ENDLINE;
			(*i)++;
		}
	}
	else if (param[*i] == '<')
	{
		cmd_line->redir_flag = REDIR_IN;
		(*i)++;
	}
}

int		check_redirection(t_cmd_line *cmd_line)
{
	char	*param;
	int		i;
	char	flag;
	int		tmp;
	
	flag = 0;
	i = 0;
	param = cmd_line->param;
	check_chacter_in_line(param, &i, &flag, is_redirection);
	tmp = i;
	set_redirection_flag(cmd_line, &i);
	check_chacter_in_line(param, &i, &flag, is_redirection);
	if (param[i] != '\0')
	{
		cmd_line->redir_flag = 0;
		return (0);
	}
	return (1);
}
// 지금 만들고자 하는 것
// redir param에 관련된 llist
// command_param을 추출하고 남은 부분을
// 공백을 기준으로 나누는거고
// but 공백은 따옴표 안에 들어있지 않은 공백이어야 함

t_list		*set_redirection_param_list()
{

}
void		set_redirection_param(t_cmd_line *cmd_line)
{
	char	*param;
	char	*value;
	int		i;
	int		len;
	char	flag;
	
	char	*redir_param;
	char	flag2;
	t_list	*list;
	
	flag = 0;
	i = 0;
	// 123 > 456 "789 999"
	//cmd param 123
	param = cmd_line->param;
	check_chacter_in_line(param, &i, &flag, is_redirection);
	value = ft_calloc(sizeof(char), i + 1);
	ft_strlcpy(value, param, i);
	remove_quotation(value);
	cmd_line->param = ft_strtrim(value, " ");
	free(value);
	
	if (cmd_line->redir_flag == OUT_ENDLINE)
		i++;
	i++;
	while (ft_isspace(param[i]))
		i++;
	redir_param = param + i;
	i = 0;
	char *start = redir_param;
	list = 0;
	char *tmp;
	while (redir_param[i])
	{
		check_chacter_in_line(redir_param, &i, &flag2, ft_isspace);
		len = (redir_param + i) - start;
		if (!redir_param[i + 1])
			len++;
		tmp = ft_calloc(sizeof(char), len + 1);
		ft_strlcpy(tmp, start, len + 1);
		remove_quotation(tmp);
		value = ft_strtrim(tmp, " ");
		free(tmp);
		if (list)
			ft_lstadd_back(&list, ft_lstnew(value));
		else
			list = ft_lstnew(value);
		i++;
		start = redir_param + i;
	}
	cmd_line->redir_param = list;
	// redir param
	// 456 - 789
	// file명 저장은 연결리스트로 변경
	// out_override인 경우는 첫번째 값만 파일 명으로 인식되고 나머지는 명령어에 대한 param으로 인식
	// redir_in인 경우에는
	// len = ft_strlen(param) - i + 1;
	// value = ft_calloc(sizeof(char), len);
	// if (cmd_line->redir_flag == OUT_ENDLINE)
	// 	i++;
	// ft_strlcpy(value, param + i + 1, len - 1);
	// remove_quotation(value);
	// cmd_line->redir_file = ft_strtrim(value, " ");
	// free(value);
}

// $ 표시가 있는가?, 변수로 저장이 되어 있는 값인가?
// echo 123 456
// $echo / 123 / 456
// void		set_env(char **str, t_list *env)
// {
// 	char	*key;
// 	char	*value;
// 	char	**key_value;

// 	if (!str || !str[0] || str[0] != '$')
// 		return (0);
// 	str++;
// 	while (env)
// 	{
// 		key_value = ft_split((char *)env->content, "=");
// 		key = key_value[0];
// 		value = key_value[1];
// 		if (are_equal(str, key))
// 		{
// 			free(key);
// 			free(key_value);
// 			free(*str);
// 			*str = value;
// 			return ;
// 		}
// 		env = env->next;
// 	}
// 	free(key_value);
// 	free(key);
// 	free(value);
// }
// char		*is_env(char *str, t_list *env)
// {
// 	char	*key;
// 	char	*value;
// 	char	**key_value;

// 	if (!str || !str[0] || str[0] != '$')
// 		return (0);
// 	else
// 		str++;
// 	while (env)
// 	{
// 		key_value = ft_split((char *)env->content, "=");
// 		key = key_value[0];
// 		value = key_value[1];
// 		if (are_equal(str, key))
// 		{
// 			free(key);
// 			free(key_value);
// 			return (value);
// 		}
// 		env = env->next;
// 	}
// 	free(key_value);
// 	free(key);
// 	free(value);
// 	return (0);
// }

bool		parse_cmd_line(t_cmd_line *cmd_line, char *start, int len, t_list *env)
{
	char	*value;
	char	*env_value;

	value = ft_calloc(sizeof(char), len + 1);
	ft_strlcpy(value, start, len + 1);
	set_env(value, env);
	remove_quotation(value);
	// ft_function for check in env valuable name
	// if ((env_value = is_env(value, env)))
	// {
	// 	free(value);
	// 	value = env_value;
	// }
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
	set_param(command_line, start);
	index += ft_strlen(command_line->param);
	check_redirection(command_line);
	if (command_line->redir_flag)
		set_redirection_param(command_line);
	else
	{
		// command_line->param free해야 함
		set_env()
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
