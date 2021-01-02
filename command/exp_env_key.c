#include "command.h"

bool	has_plus(char *env_key)
{
	int		len;

	if (!env_key)
		return (false);
	len = ft_strlen(env_key);
	if (env_key[len - 1] == '+')
		return (true);
	return (false);
}

void	check_end_in_plus(t_export *exp_info, char *env_key)
{
	if (has_plus(env_key))
	{
		exp_info->end_in_plus = true;
		env_key[ft_strlen(env_key) - 1] = '\0';
	}
}

bool	validate_env_key(char *env_key)
{
	int		i;

	i = 0;
	if (!env_key)
		return (true);
	if (!(*env_key))
		return (false);
	while (env_key[i] && env_key[i] != '=')
	{
		if (is_contained(env_key[i], "!@#$%^&*()_+")
			|| is_contained(env_key[i], "0123456789"))
			return (false);
		i++;
	}
	return (true);
}

char	*trim_key_value(char *key_value, t_export *exp_info)
{
	char	*separator;
	char	*key;

	separator = ft_strchr(key_value, '=');
	if (separator)
	{
		exp_info->has_separator = true;
		*separator = '\0';
		key = ft_strdup(key_value);
		*separator = '=';
		check_end_in_plus(exp_info, key);
	}
	else
		key = ft_strdup(key_value);
	return (key);
}

char	*get_env_key(char *param, t_cmd_line *cmd_line, t_export *exp_info)
{
	char	*key;
	char	*key_value;

	if (!(key_value = ft_strdup(param)))
		return (NULL);
	key = trim_key_value(key_value, exp_info);
	if (!validate_env_key(key))
	{
		make_err_msg(EXIT_FAILURE, cmd_line->command, key_value,
					get_err_msg(INVALID_EXPORT_PARAM));
		free(key_value);
		free(key);
		return (NULL);
	}
	free(key_value);
	return (key);
}
