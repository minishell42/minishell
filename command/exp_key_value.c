#include "command.h"

char	*get_value(char *str)
{
	char	*key_value;
	char	*separator;
	char	*value;

	value = NULL;
	if (!(key_value = ft_strdup(str)))
		return (NULL);
	if ((separator = ft_strchr(key_value, '=')))
		value = ft_strdup(separator + 1);
	free(key_value);
	return (value);
}

char	*join_key_value(char *env_key, char *key_value)
{
		char	*strs[4];
		char	*res;
		int		i;

		ft_bzero(strs, sizeof(strs));
		strs[0] = ft_strdup(env_key);
		strs[1] = ft_strdup("=");
		strs[2] = get_value(key_value);
		res = ft_join_strs(strs);
		i = 0;
		while (strs[i])
			free(strs[i++]);
		return (res);
}

bool	validate_key_value(char *key_value, t_cmd_line *cmd_line)
{
	if (*key_value == '=')
	{
		make_err_msg(EXIT_FAILURE, cmd_line->command,	key_value,
					get_err_msg(INVALID_EXPORT_PARAM));
		return (false);
	}
	return (true);
}