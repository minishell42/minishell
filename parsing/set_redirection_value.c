#include "parsing.h"

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

static char	*set_param_before_redir(t_cmd_line *cmd_line, t_list *env)
{
	char	*param;
	char	flag;
	char	*value;
	int		i;

	flag = 0;
	i = 0;
	param = cmd_line->param;
	check_chacter_in_line(param, &i, &flag, is_redirection);
	cmd_line->param = convert_to_valid_value(param, i, env);
	if (cmd_line->redir_flag == OUT_ENDLINE)
		i++;
	i++;
	while (ft_isspace(param[i]))
		i++;
	return (param + i);
}

void	get_redirection_param(char *str, t_list *env, t_list **list)
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
		check_chacter_in_line(str, &i, &flag, ft_isspace);
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
}

void	set_redirection_param(t_cmd_line *cmd_line, t_list *env)
{
	char	*redir_param;
	t_list	*list;

	redir_param = set_param_before_redir(cmd_line, env);
	list = 0;
	get_redirection_param(redir_param, env, &list);
	cmd_line->redir_param = list;
}
