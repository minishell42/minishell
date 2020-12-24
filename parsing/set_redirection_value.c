#include "parsing.h"

// --------------------- before -----------------------------
// void	set_redirection_flag(t_cmd_line *cmd_line, int *i)
// {
// 	char *param;

// 	param = cmd_line->param;
// 	if (param[*i] == '>')
// 	{
// 		cmd_line->redir_flag = OUT_OVERRIDE;
// 		if (param[++(*i)] == '>')
// 		{
// 			cmd_line->redir_flag = OUT_ENDLINE;
// 			(*i)++;
// 		}
// 	}
// 	else if (param[*i] == '<')
// 	{
// 		cmd_line->redir_flag = REDIR_IN;
// 		(*i)++;
// 	}
// }

// static char	*set_param_before_redir(t_cmd_line *cmd_line, t_list *env, char *param)
// {
// 	char	flag;
// 	char	*value;
// 	int		i;

// 	flag = 0;
// 	i = 0;
// 	if (!check_character_in_line(param, &i, is_redirection))
// 		return (NULL);
// 	cmd_line->param = convert_to_valid_value(param, i, env);
// 	if (cmd_line->redir_flag == OUT_ENDLINE)
// 		i++;
// 	i++;
// 	while (ft_isspace(param[i]))
// 		i++;
// 	return (param + i);
// }

// static bool	get_redirection_param(char *str, t_list *env, t_list **list)
// {
// 	char	*start;
// 	int		i;
// 	char	flag;
// 	int		len;
// 	char	*value;
	
// 	start = str;
// 	i = 0;
// 	while (str[i])
// 	{
// 		if (!check_character_in_line(str, &i, ft_isspace))
// 			return (false);
// 		len = (str + i) - start;
// 		if (!str[i + 1])
// 			len++;
// 		value = convert_to_valid_value(start, len, env);
// 		if (*list)
// 			ft_lstadd_back(list, ft_lstnew(value));
// 		else
// 			*list = ft_lstnew(value);
// 		i++;
// 		start = str + i;
// 	}
// 	return (true);
// }

// static void	integrate_param(t_cmd_line *cmd_line)
// {
// 	char	*ret;
// 	char	*tmp;
// 	t_list	*head;

// 	ret = ft_strdup(cmd_line->param);
// 	free(cmd_line->param);
// 	head = cmd_line->redir_param->next;
// 	while (head)
// 	{
// 		tmp = ft_strjoin(ret, " ");
// 		free(ret);
// 		ret = ft_strjoin(tmp, (char*)head->content);
// 		free(tmp);
// 		head = head->next;
// 	}
// 	cmd_line->param = ret;
// 	ft_lstclear(&(cmd_line->redir_param->next), free);
// 	cmd_line->redir_param->next = NULL;
// }

// bool	set_redirection_param(t_cmd_line *cmd_line, t_list *env)
// {
// 	char	*redir_param;
// 	char	*start;
// 	t_list	*list;

// 	start = cmd_line->param;
// 	if (!(redir_param = set_param_before_redir(cmd_line, env, start))
// 		|| !(*redir_param))
// 		{
// 			free(start);
// 			return (false);
// 		}
// 	list = 0;
// 	if (!get_redirection_param(redir_param, env, &list))
// 	{
// 		free(start);
// 		return (false);
// 	}
// 	cmd_line->redir_param = list;
// 	integrate_param(cmd_line);
// 	free(start);
// 	return (true);
// }

// ------------------------ after ------------------------------------

// redir 표시 전의 param 값 입력 (bool type)
//------- finish function --------
bool	set_param_before_redir(t_cmd_line *cmd_line, t_list *env, char *param, int *index)
{
	char	*before_param;
	
	printf("param ? '%s'\n", param);
	if (!check_character_in_line(param, index, is_redirection))
		return (false);
	if (!(before_param = ft_substr(param, 0, *index)))
		return (false);
	cmd_line->param = convert_to_valid_value(before_param, ft_strlen(before_param), env);
	printf("index ? %d\tget param ? %s\n", *index, cmd_line->param);
	free(before_param);
	// printf("end set_param_before_redir\n");
	return (true);
}

static char	*set_err_redir_out(const char *redir_out, char * content)
{
	char	*err_point;

	if (redir_out != content && *(redir_out - 1) == '>')
		err_point = ft_strdup(">>");
	else
		err_point = ft_strdup(">");
	return (err_point);
}
// echo 123 > 123 > < >>
// >> s
void	set_err_point(int redir_flag, char *content)
{
	char		*err_point;
	const char	*redir_in;
	const char	*redir_out;

	err_point = 0;
	redir_in = ft_strrchr(content, '<');
	redir_out = ft_strrchr(content, '>');
	if (!redir_in && redir_out)
		err_point = set_err_redir_out(redir_out, content);
	else if (!redir_out && redir_in)
		err_point = ft_strdup("<");
	else if (redir_in && redir_in > redir_out)
		err_point = ft_strdup("<");
	else if (redir_out && redir_out > redir_in)
		err_point = set_err_redir_out(redir_out, content);
	if (err_point)
		parsing_err_value(SYNTAX_ERROR, err_point);
	free(err_point);
}

bool	set_redir_flag(t_redir *redir, char *param, char **content)
{
	if (**content == '>')
	{
		redir->redir_flag = OUT_OVERRIDE;
		(*content)++;
		if (**content == '>')
		{
			(*content)++;
			redir->redir_flag = OUT_ENDLINE;
		}
	}
	else if (**content == '<')
	{
		(*content)++;
		redir->redir_flag = REDIR_IN;
	}
	while (ft_isspace(**content))
		(*content)++;
	if (**content == '\0')
	{
		// printf("here!!\n");
		set_err_point(redir->redir_flag, param);
		return (false);
	}
	return (true);
}

bool	set_other_param(t_cmd_line *cmd_line, t_list *env, char *content, int index)
{
	char	*tmp;
	char	*sub_param;
	char	*other_param;

	if (!(sub_param = ft_substr(content, index, ft_strlen(content) - index)))
		return (false);
	if (!(tmp = ft_strjoin(cmd_line->param, sub_param)))
	{
		free(sub_param);
		return (false);
	}
	free(sub_param);
	if (!(other_param = convert_to_valid_value(tmp, ft_strlen(tmp), env)))
	{
		free(tmp);
		return (false);
	}
	free(tmp);
	free(cmd_line->param);
	cmd_line->param = other_param;
	return (true);
}


// redir 구조체 param에 값을 넣을 것 // 오류 1번을 고려할 것 // space를 기준으로 더 있을 시 param에 값을 옮겨줄 것
// content = ' 123 4 '에 해당
bool	set_redir_param(t_cmd_line *cmd_line, t_list *env, t_redir *redir, char *content)
{
	int		index;
	char	*tmp;

	index = 0;
	// space를 기준으로 값 나눈 다.
	if (content[index] && check_character_in_line(content, &index, ft_isspace))
		tmp = ft_substr(content, 0, index);
	// 처음 값을 redir 구조체 param에 넣어준다.
	if (!(redir->redir_param = convert_to_valid_value(tmp, ft_strlen(tmp), env)))
	{
		free(tmp);
		return (false);
	}
	free(tmp);
	// 뒤에 값이 더 있으면 cmd_line param에 값을 join 하여 붙여 넣기
	if (!set_other_param(cmd_line, env, content, index))
		return (false);
	return (true);
}

// redir 연결 리스트를 생성해서 cmd_line에 넘겨준다.
// 오류에 해당되는 부분 
// 1. redir flag는 존재하나 param을 trim을 했을 때 존재하지 않는 경우
// 1-1. 해당 error point를 parsing err해야한다.
// 2. 메모리 할당에 실패했을 경우
// content = '> 123 4 '에 해당
// flag를 세울대 > 과 >>을 조심해서 세울것 and 그 플레그를 지난 다음 index로 옮겨줄 것
bool	can_make_redir_list(t_cmd_line *cmd_line, t_list *env, char *param, char *content)
{
	t_redir		*redir;
	t_list		*list;
	char		*tmp;

	list = cmd_line->redir_param;
	tmp = content;
	// redir 구조체 생성
	if (!(redir = ft_calloc(sizeof(t_redir), 1)))
		return (false);
	// 구조체에 flag값 넣기
	if (!(set_redir_flag(redir, param, &tmp)))
	{
		free(redir);
		return (false);
	}
	// redir 구조체 param에 값을 넣을 것 // 오류 1번을 고려할 것 //v space를 기준으로 더 있을 시 param에 값을 옮겨줄 것
	if (!(set_redir_param(cmd_line, env, redir, tmp)))
	{
		free(redir);
		return (false);
	}
	// 연결 리스트 생성 및 연결
	ft_lstadd_back(&list, ft_lstnew(redir));
	cmd_line->redir_param = list;
	return (true);
}

// redir 표시 이후의 값을 space를 기준으로 넣기
// param > 표시부터 시작되서 끝까지의 값 : ex) echo 123 > 123 4 > 222 일때 > 123 4 > 222에 해당됨
// param은 trim이 된 상태에서 넘어옴 + 환경 변수값이 변환된 상태에서 넘어옴

bool	get_redirection_param(t_cmd_line *cmd_line, t_list *env, char *param, int *index)
{
	int			start;
	char		*redir_content;

	printf("param2 ? '%s'\n", param); //> 123 4 > 222
	// 처음 스타트 부분 담기 : '>'
	start = (*index)++;
	// while을 돌면서 redir 부분 찾기 ? 기준 '>'표시
	while (param[*index] && check_character_in_line(param, index, is_redirection))
	{
		//override와 endline  구분
		if (param[*index] == '>' && start + 1 == *index)
		{
			(*index)++;
			check_character_in_line(param, index, is_redirection);
		}
		// redir 연결리스트를 생성하기 전에 start ~ index까지 해당되는 글자들을 가진 문자열 생성해서 파라미터로 넘겨줄 예정
		if (!(redir_content = ft_substr(param, start, *index - start)))
			return (false);
		start = *index;
		printf("index ? %d\tredir_content ? %s\n", *index, redir_content);
		// redir 연결 리스트를 생성해서 cmd_line redir_param에 대입
		if (!can_make_redir_list(cmd_line, env, param, redir_content))
		{
			free(redir_content);
			return (false);
		}
		free(redir_content);
		if (param[*index] != '\0')
			(*index)++;
	}
	// error 처리 따옴표가 제대로 닫히지 않아서 종료되는 경우
	if (g_err.err_number)
		return (false);
	// printf("end get_redirection_param\n");
	return (true);
}

bool	set_redirection_param(t_cmd_line *cmd_line, t_list *env)
{
	char	*param;
	char	*tmp;
	int		index;

	param = cmd_line->param;
	index = 0;
	// redir 표시 전의 param 값 입력 (bool type)
	if (!set_param_before_redir(cmd_line, env, param, &index))
		return (false);
	// redir 표시 와 그에 해당되는 값을 찾아서 넣기
	if (!get_redirection_param(cmd_line, env, param, &index))
	{
		free(param);
		return (false);
	}
	// param free : 새로운 param이나 redir 값은 메모리 할당을 다시하여 넣기 때문에
	free(param);
	// printf("end set_redirection_param\n");
	return (true);
}
