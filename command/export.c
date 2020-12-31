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

	if(!(key_value = ft_strdup(param)))
		return (NULL);
	key = trim_key_value(key_value, exp_info);
	if (!validate_env_key(key))
	{
		make_err_msg(cmd_line->command, key_value,
					get_err_msg(INVALID_EXPORT_PARAM));
		free(key_value);
		free(key);
		return (NULL);
	}
	free(key_value);
	return (key);
}

static char	*get_value(char *str)
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

bool	update_value(t_list *target_llist, t_export *exp_info)
{
	char	*content;
	char	*env_value;
	
	if (exp_info->end_in_plus)
	{
		content = target_llist->content;
		env_value = get_value(exp_info->key_value);
		target_llist->content = ft_strjoin(content, env_value);
		free(content);
		free(env_value);
	}
	else
	{
		content = target_llist->content;
		target_llist->content = ft_strdup(exp_info->key_value);
		free(content);
	}
	return (true);
}

bool	add_new_key_value(t_export *exp_info)
{
	char	*new_key_value;
	char	*env_key;
	char	*key_value;

	env_key = exp_info->env_key;
	key_value = exp_info->key_value;
	if (exp_info->end_in_plus)
		{
			if (!(new_key_value = join_key_value(env_key, key_value)))
				return (false);
			ft_lstadd_back(&g_env, ft_lstnew(new_key_value));
		}
		else
			ft_lstadd_back(&g_env, ft_lstnew(ft_strdup(key_value)));
	return (true);
}

bool	update_env(t_export *exp_info)
{
	t_list	*target_llist;

	if (!exp_info->has_separator)
		return (true);
	if((target_llist = find_env_target_list(exp_info->env_key)))
	{
		if (!update_value(target_llist, exp_info))
			return (false);
	}
	else
	{
		if (!add_new_key_value(exp_info))
			return (false);
	}
	return (true);
}

void	free_export(t_export *exp_info)
{
	if (exp_info->env_key)
		free(exp_info->env_key);
	free(exp_info);
}

bool	validate_key_value(char *key_value, t_cmd_line *cmd_line)
{
	if (*key_value == '=')
	{
		make_err_msg(cmd_line->command,	key_value,
					get_err_msg(INVALID_EXPORT_PARAM));
		return (false);
	}
	return (true);
}

t_export	*init_export(t_cmd_line *cmd_line, char **key_values, char *key_value)
{
	t_export	*exp_info;
	char		*env_key;
	
	if (!validate_key_value(key_value, cmd_line))
		return (NULL);
	if (!(exp_info = ft_calloc(sizeof(t_export), 1)))
		return (NULL);
	exp_info->key_value = key_value;
	exp_info->key_values = key_values;
	exp_info->end_in_plus = false;
	if (!(exp_info->env_key = get_env_key(key_value, cmd_line, exp_info)))
	{
		free_export(exp_info);
		return (NULL);
	}
	return (exp_info);
}

void	print_content_exp(void *content)
{
	int		len;
	char	*str;

	if (!content)
		return ;
	str = content;
	len = ft_strlen(content);
	str[len] = '\n';
	write(1, "declare -x ", 11);
	write(1, str, len + 1);
	str[len] = '\0';
}

bool	export(t_cmd_line *cmd_line)
{
	t_export	*exp_info;
	char		**key_values;
	int			ret;
	int			i;

	if (!cmd_line->param)
		ft_lstiter(g_env, print_content_exp);
	ret = true;
	key_values = convert_to_array_env_list(cmd_line->param);
	i = 0;
	while (key_values[i])
	{
		if (!(exp_info = init_export(cmd_line, key_values, key_values[i]))
			|| !(update_env(exp_info)))
			ret = false;
		if (exp_info)
			free_export(exp_info);
		i++;
	}
	free(key_values);
	return (ret);
}
