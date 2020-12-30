#include "parsing.h"

static int		check_start_line(char *line, int i)
{
	if (!line || !(*line))
		return (0);
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (line[i] == ';' || line[i] == '|')
		return (set_syntax_err(line, i));
	return (1);
}

static int		check_validate_line(char *line, char *flag)
{
	int	i;
	
	i = 0;
	while (line[i])
	{
		while (line[i] && !is_delimitor(line[i]))
			i++;
		if (line[i] && !*flag)
		{
			*flag = line[i++];
			if (*flag == '>' && line[i] == '>')
				i++;
		}
		while (ft_isspace(line[i]))
			i++;
		if (*flag && is_delimitor(line[i]))
			return (set_syntax_err(line, i));
		if (line[i])
		{
			*flag = 0;
			i++;
		}
	}
	return (1);
}

int				validate_line(char *line)
{	
	int		i;
	char	flag;
	
	i = 0;
	flag = 0;
	if (!check_start_line(line, i))
		return (0);
	if (!check_validate_line(line + i, &flag))
		return (0);
	if (flag && flag != ';')
	{
		make_err_msg(0, 0, get_err_msg(PARAM_IS_NEWLINE));
		return (false);
	}
	return (1);
}
