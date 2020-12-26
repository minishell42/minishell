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
	
	if (!check_character_in_line(param, index, is_redirection))
		return (false);
	if (!(before_param = ft_substr(param, 0, *index)))
		return (false);
	cmd_line->param = convert_to_valid_value(before_param, ft_strlen(before_param), env);
	free(before_param);
	return (true);
}

// static char	*set_err_redir_out(const char *redir_out, char * content)
// {
// 	char	*err_point;

// 	if (redir_out != content && *(redir_out - 1) == '>')
// 		err_point = ft_strdup(">>");
// 	else
// 		err_point = ft_strdup(">");
// 	return (err_point);
// }

// void	set_err_point(int redir_flag, char *content)
// {
// 	char		*err_point;
// 	const char	*redir_in;
// 	const char	*redir_out;

// 	err_point = 0;
// 	redir_in = ft_strrchr(content, '<');
// 	redir_out = ft_strrchr(content, '>');
// 	if (!redir_in && redir_out)
// 		err_point = set_err_redir_out(redir_out, content);
// 	else if (!redir_out && redir_in)
// 		err_point = ft_strdup("<");
// 	else if (redir_in && redir_in > redir_out)
// 		err_point = ft_strdup("<");
// 	else if (redir_out && redir_out > redir_in)
// 		err_point = set_err_redir_out(redir_out, content);
// 	if (err_point)
// 		parsing_err_value(SYNTAX_ERROR, err_point);
// 	free(err_point);
// }

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
		return (false);
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

bool	set_redir_param(t_cmd_line *cmd_line, t_list *env, t_redir *redir, char *content)
{
	int		index;
	char	*tmp;

	index = 0;
	if (content[index] && check_character_in_line(content, &index, ft_isspace))
		tmp = ft_substr(content, 0, index);
	if (!(redir->redir_param = convert_to_valid_value(tmp, ft_strlen(tmp), env)))
	{
		free(tmp);
		return (false);
	}
	free(tmp);
	if (!set_other_param(cmd_line, env, content, index))
		return (false);
	return (true);
}

bool	can_make_redir_list(t_cmd_line *cmd_line, t_list *env, char *param, char *content)
{
	t_redir		*redir;
	t_list		*list;
	char		*tmp;

	list = cmd_line->redir_param;
	tmp = content;
	if (!(redir = ft_calloc(sizeof(t_redir), 1)))
		return (false);
	if (!(set_redir_flag(redir, param, &tmp)))
	{
		free(redir);
		return (false);
	}
	if (!(set_redir_param(cmd_line, env, redir, tmp)))
	{
		free(redir);
		return (false);
	}
	ft_lstadd_back(&list, ft_lstnew(redir));
	cmd_line->redir_param = list;
	return (true);
}

bool	get_redirection_param(t_cmd_line *cmd_line, t_list *env, char *param, int *index)
{
	int			start;
	char		*redir_content;

	start = (*index)++;
	while (param[*index] && check_character_in_line(param, index, is_redirection))
	{
		if (param[*index] == '>' && start + 1 == *index)
		{
			(*index)++;
			check_character_in_line(param, index, is_redirection);
		}
		if (!(redir_content = ft_substr(param, start, *index - start)))
			return (false);
		start = *index;
		if (!can_make_redir_list(cmd_line, env, param, redir_content))
		{
			free(redir_content);
			return (false);
		}
		free(redir_content);
		if (param[*index] != '\0')
			(*index)++;
	}
	if (g_err.err_number)
		return (false);
	return (true);
}

bool	set_redirection_param(t_cmd_line *cmd_line, t_list *env)
{
	char	*param;
	char	*tmp;
	int		index;

	param = cmd_line->param;
	index = 0;
	if (!set_param_before_redir(cmd_line, env, param, &index))
		return (false);
	if (!get_redirection_param(cmd_line, env, param, &index))
	{
		free(param);
		return (false);
	}
	free(param);
	return (true);
}
