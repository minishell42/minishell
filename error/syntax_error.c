#include "ft_error.h"

void	set_quot_err(char quot_flag)
{
	char	*err_value;

	if (!(err_value = ft_calloc(sizeof(char), 2)))
		return ;
	err_value[0] = quot_flag;
	make_err_msg(SYNTAX_ERROR, 0, err_value, get_err_msg(QUOT_IS_NOT_PAIR));
	free(err_value);
}

int		set_syntax_err(char *line, int i)
{
	char	*err_value;

	err_value = ft_calloc(sizeof(char), 3);
	err_value[0] = line[i];
	if (line[i] == line[i - 1] || line[i] == line[i + 1])
		err_value[1] = line[i];
	make_err_msg(SYNTAX_ERROR, 0, err_value, get_err_msg(SYNTAX_ERROR));
	free(err_value);
	return (0);
}
