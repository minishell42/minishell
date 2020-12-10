#include "parsing.h"

int			is_separator(int c)
{
	if (c == ';' || c == '|')
		return (true);
	return (false);
}

int			is_redirection(int c)
{
	if (c == '<' || c == '>')
		return (true);
	return (false);
}

int			is_semicolon(int c)
{
	if (c == ';')
	{
		return (true);
	}
	return (false);
}

void		check_chacter_in_line(char *line, 
					int *index, char *quot_flag, int (*func)())
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

int			check_redirection(t_cmd_line *cmd_line)
{
	char	*param;
	int		i;
	char	flag;
	
	flag = 0;
	i = 0;
	param = cmd_line->param;
	check_chacter_in_line(param, &i, &flag, is_redirection);
	set_redirection_flag(cmd_line, &i);
	check_chacter_in_line(param, &i, &flag, is_redirection);
	if (param[i] != '\0')
	{
		cmd_line->redir_flag = 0;
		return (0);
	}
	return (1);
}
