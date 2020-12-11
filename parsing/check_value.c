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

static void	set_quot_err(char quot_flag)
{
	if (!(g_err.err_value = ft_calloc(sizeof(char), 2)))
		g_err.err_number = ALLOC_ERROR;
	else
	{
		g_err.err_value[0] = quot_flag;
		g_err.err_number = QUOT_IS_NOT_PAIR;
	}
}

bool		check_character_in_line(char *line, 
					int *index, int (*func)())
{
	char	quot_flag;

	quot_flag = 0;
	while (line[*index] && !(func(line[*index]) && quot_flag == 0))
	{
		if (line[*index] == '\'' || line[*index] == '"')
		{
			if (quot_flag == line[*index])
				quot_flag = 0;
			else if (quot_flag == 0)
				quot_flag = line[*index];
		}
		(*index)++;
	}
	if (quot_flag)
	{
		set_quot_err(quot_flag);
		return (false);
	}
	return (true);
}

bool		check_redirection(t_cmd_line *cmd_line)
{
	char	*param;
	int		i;
	char	flag;
	
	flag = 0;
	i = 0;
	param = cmd_line->param;
	if (!check_character_in_line(param, &i, is_redirection))
		return (false);
	set_redirection_flag(cmd_line, &i);
	if (!check_character_in_line(param, &i, is_redirection))
		return (false);
	if (param[i] != '\0')
	{ 
		g_err.err_number = TOO_MANY_REDIR;
		cmd_line->redir_flag = 0;
		return (false);
	}
	return (true);
}
