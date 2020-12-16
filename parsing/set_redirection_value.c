#include "parsing.h"

void	set_redirection_flag(t_cmd_line *cmd_line, int *i)
{
	char *param;

	param = cmd_line->param;
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

static char	*set_param_before_redir(t_cmd_line *cmd_line, t_list *env, char *param)
{
	char	flag;
	char	*value;
	int		i;

	flag = 0;
	i = 0;
	if (!check_character_in_line(param, &i, is_redirection))
		return (NULL);
	cmd_line->param = convert_to_valid_value(param, i, env);
	if (cmd_line->redir_flag == OUT_ENDLINE)
		i++;
	i++;
	while (ft_isspace(param[i]))
		i++;
	return (param + i);
}

static bool	get_redirection_param(char *str, t_list *env, t_list **list)
{
	char	*start;
	int		i;
	char	flag;
	int		len;
	char	*value;
	
	start = str;
	i = 0;
	while (str[i])
	{
		if (!check_character_in_line(str, &i, ft_isspace))
			return (false);
		len = (str + i) - start;
		if (!str[i + 1])
			len++;
		value = convert_to_valid_value(start, len, env);
		if (*list)
			ft_lstadd_back(list, ft_lstnew(value));
		else
			*list = ft_lstnew(value);
		i++;
		start = str + i;
	}
	return (true);
}

static void	integrate_param(t_cmd_line *cmd_line)
{
	char	*ret;
	char	*tmp;
	t_list	*head;

	ret = ft_strdup(cmd_line->param);
	free(cmd_line->param);
	head = cmd_line->redir_param->next;
	while (head)
	{
		tmp = ft_strjoin(ret, " ");
		free(ret);
		ret = ft_strjoin(tmp, (char*)head->content);
		free(tmp);
		head = head->next;
	}
	cmd_line->param = ret;
	ft_lstclear(&(cmd_line->redir_param->next), free);
	cmd_line->redir_param->next = NULL;
}

bool	set_redirection_param(t_cmd_line *cmd_line, t_list *env)
{
	char	*redir_param;
	char	*start;
	t_list	*list;

	start = cmd_line->param;
	if (!(redir_param = set_param_before_redir(cmd_line, env, start))
		|| !(*redir_param))
		{
			free(start);
			return (false);
		}
	list = 0;
	if (!get_redirection_param(redir_param, env, &list))
	{
		free(start);
		return (false);
	}
	cmd_line->redir_param = list;
	integrate_param(cmd_line);
	free(start);
	return (true);
}
