#include "parsing.h"

// -------------------------  before  --------------------------------
// bool	set_param_before_redir(t_cmd_line *cmd_line, 
// 								t_list *env, char *param, int *index)
// {
// 	char	*before_param;
	
// 	if (!check_character_in_line(param, index, is_redirection))
// 		return (false);
// 	if (!(before_param = ft_substr(param, 0, *index)))
// 		return (false);
// 	cmd_line->param = before_param;
// 	return (true);
// }

// -------------------------  after  --------------------------------

bool	set_param_before_redir(t_cmd_line *cmd_line, 
								char *param, int *index)
{
	char	*before_param;
	
	// printf("in set_param_before_redir\n");
	if (!check_character_in_line(param, index, is_redirection))
		return (false);
	if (!(before_param = ft_substr(param, 0, *index)))
		return (false);
	// printf("index ? %d\n", *index);
	cmd_line->param = make_param_list(before_param);
	free(before_param);
	return (true);
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
		return (false);
	return (true);
}

// ---------------------------  before  ------------------------------
// bool	set_other_param(t_cmd_line *cmd_line, 
// 						t_list *env, char *content, int index)
// {
// 	char	*sub_param;
// 	char	*other_param;

// 	if (!(sub_param = 
// 			ft_substr(content, index, ft_strlen(content) - index)))
// 		return (false);
// 	if (!(other_param = ft_strjoin(cmd_line->param, sub_param)))
// 	{
// 		free(sub_param);
// 		return (false);
// 	}
// 	free(sub_param);
// 	free(cmd_line->param);
// 	cmd_line->param = other_param;
// 	return (true);
// }

// ---------------------------  after  ------------------------------
bool	set_other_param(t_cmd_line *cmd_line, 
						char *content, int index)
{
	char	*other_param;
	t_list	*other_param_list;
	t_list	*tmp;

	if (!(other_param = 
			ft_substr(content, index, ft_strlen(content) - index)))
		return (false);
	// printf("other param ? '%s'\n", other_param);
	other_param_list = make_param_list(other_param);
	tmp = ft_lstlast(cmd_line->param);
	tmp->next = other_param_list;
	// printf("other param list size ? '%d'\n", ft_lstsize(other_param_list));
	// printf("param list size ? '%d'\n", ft_lstsize(tmp));
	free(other_param);
	return (true);
}

bool	set_redir_param(t_cmd_line *cmd_line, 
						t_redir *redir, char *content)
{
	int		index;
	char	*tmp;

	// printf("in set_redir_param\n");
	index = 0;
	if (content[index] && 
			check_character_in_line(content, &index, ft_isspace))
		tmp = ft_substr(content, 0, index);
	// printf("set_redir_paramk before? '%s'\n", tmp);
	if (!(redir->redir_param = 
			convert_to_valid_value(tmp, ft_strlen(tmp))))
	{
		free(tmp);
		return (false);
	}
	// printf("set_redir_param after ? '%s'\n", redir->redir_param);
	free(tmp);
	if (!set_other_param(cmd_line, content, index))
		return (false);
	return (true);
}

bool	can_make_redir_list(t_cmd_line *cmd_line, 
							char *param, char *content)
{
	t_redir		*redir;
	t_list		*list;
	char		*tmp;

	// printf("in can_make_redir_list\n");
	list = cmd_line->redir_param;
	tmp = content;
	if (!(redir = ft_calloc(sizeof(t_redir), 1)))
		return (false);
	if (!(set_redir_flag(redir, param, &tmp)))
	{
		free(redir);
		return (false);
	}
	// printf("what is content ? '%s'\n", tmp);
	if (!(set_redir_param(cmd_line, redir, tmp)))
	{
		free(redir);
		return (false);
	}
	ft_lstadd_back(&list, ft_lstnew(redir));
	cmd_line->redir_param = list;
	return (true);
}

bool	get_redirection_param(t_cmd_line *cmd_line, 
								char *param, int *index)
{
	int			start;
	char		*redir_content;

	// printf("in get_redirection_param\n");
	// printf("what is param ? '%s'\n", param);
	start = (*index)++;
	while (param[*index] != '\0' && 
			check_character_in_line(param, index, is_redirection))
	{
		if (param[*index] == '>' && start + 1 == *index)
		{
			(*index)++;
			check_character_in_line(param, index, is_redirection);
		}
		if (!(redir_content = ft_substr(param, start, *index - start)))
			return (false);
		start = *index;
		if (!can_make_redir_list(cmd_line, param, redir_content))
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
// -------------------------  before ---------------------------------
// bool	set_redirection_param(t_cmd_line *cmd_line, t_list *env)
// {
// 	char	*param;
// 	char	*tmp;
// 	int		index;

// 	param = cmd_line->param;
// 	index = 0;
// 	if (!set_param_before_redir(cmd_line, env, param, &index))
// 		return (false);
// 	if (!get_redirection_param(cmd_line, env, param, &index))
// 	{
// 		free(param);
// 		return (false);
// 	}
// 	free(param);
// 	return (true);
// }
// -------------------------  after ---------------------------------
bool	set_redirection_param(t_cmd_line *cmd_line)
{
	char	*param;
	t_list	*param_list;
	char	*tmp;
	int		index;

	param_list = cmd_line->param;
	param = (char *)cmd_line->param->content;
	index = 0;
	if (!set_param_before_redir(cmd_line, param, &index))
		return (false);
	if (!get_redirection_param(cmd_line, param, &index))
	{
		free(param);
		free(param_list);
		return (false);
	}
	free(param);
	free(param_list);
	return (true);
}
