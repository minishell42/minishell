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
}
