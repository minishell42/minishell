#include "command.h"

bool	validate_exp_param(char *param)
{
	int		i;

	i = 0;
	if (param[0] == '=')
		return (parsing_err_value(INVALID_EXPORT_PARAM, param));
	if (ft_strchr(param, '='))
	{
		while (param[i] != '=')
		{
			if (is_contained(param[i], "!@#$%^&*()_+"))
				return (parsing_err_value(INVALID_EXPORT_PARAM,
											param));
			i++;
		}
	}
	return (true);
		
}

char	*export(t_cmd_line *cmd_line, t_list *env, char* pipe_input)
{
	char	**key_values;
	int		i;

	key_values = ft_split(cmd_line->param, ' ');
	i = 0;
	while (key_values[i])
	{
		if (validate_exp_param(key_values[i]))
			ft_lstadd_back(&env, ft_lstnew(ft_strdup(key_values[i])));
		i++;
	}
	free_str_array(key_values);
	return (NULL);
}
