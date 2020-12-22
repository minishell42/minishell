#include "utils.h"

void		remove_quotation(char *value)
{
	char		quot_flag;
	int			index;

	quot_flag = 0;
	while (value && *value)
	{
		index = 0;
		while (*value && *value != '"' && *value != '\'')
			value++;
		if (*value == '"' || *value == '\'')
		{
			if (quot_flag == 0)
				quot_flag = *value;
			else if (quot_flag == *value)
				quot_flag = 0;
		}
		if (quot_flag == *value || quot_flag == 0)
			while (value && value[index++])
				value[index - 1] = value[index];
		else
			value++;
	}
}

void	free_str_array(char **strs)
{
	int			i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

bool	is_contained(char c, char *str)
{
	int			i;

	i = 0;
	while (str[i])
	{
		if (c == str[i])
		{
			return (true);
		}
		i++;
	}
	return (0);
}
