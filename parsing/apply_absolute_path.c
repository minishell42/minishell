#include "parsing.h"

static char	*get_absolute_path(char *value, int index)
{
	char	*tmp;
	char	*result;
	int		curr_len;

	curr_len = 0;
	result = NULL;
	if (index != 0 && value[index - 1] == '.')
	{
		tmp = getcwd(NULL, 0);
		if (index != 1 && value[index - 2] == '.')
		{
			curr_len = ft_strlen(tmp) - 1;
			while (curr_len >= 0 && tmp[curr_len] != '/')
			{
				tmp[curr_len] = '\0';
				curr_len--;
			}
			if (tmp[curr_len] == '/')
				tmp[curr_len] = '\0';
		}
		result = ft_strjoin(tmp, value + index);
		free(tmp);
	}
	else
		result = apply_tilde_expansion(value);
	return (result);
}

char		*change_to_absolute_path(char *value)
{
	char	*result;
	char	*tmp;
	int		i;
	int		curr_len;

	tmp = NULL;
	result = NULL;
	i = 0;
	while (value[i] && value[i] != '/')
		i++;
	if (!value[i])
	{
		if ((!are_equal(value, ".") && !are_equal(value, "..")))
			return (0);
	}
	result = get_absolute_path(value, i);
	return (result);
}
