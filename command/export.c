#include "command.h"

bool	validate_env_key(char *env_key)
{
	int		i;

	i = 0;
	if (!env_key)
		return (true);
	while (env_key[i] && env_key[i] != '=')
	{
		if (is_contained(env_key[i], "!@#$%^&*()_+"))
			return (false);
		i++;
	}
	return (true);
}

char	*get_env_key(char *param)
{
	char	*key;
	char	*key_value;
	char	*separator;

	key = NULL;
	key_value = ft_strdup(param);
	separator = ft_strchr(key_value, '=');
	if (separator)
	{
		*separator = '\0';
		key = ft_strdup(key_value);
	}
	free(key_value);
	return (key);
}

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

bool		free_and_set_error(char **str_array, char *err_value)
{
	parsing_err_value(INVALID_EXPORT_PARAM, err_value);
	free_str_array(str_array);
	return (false);
}

static char	*get_value(char *str)
{
	char	*key_value;
	char	*separator;
	char	*value;

	value = NULL;
	key_value = ft_strdup(str);
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

bool	update_value(bool end_in_plus, t_list *target_llist, char *input)
{
	char	*content;
	char	*env_value;
	
	if (end_in_plus)
	{
		content = target_llist->content;
		env_value = get_value(input);
		printf("env value = %s\n", env_value);
		target_llist->content = ft_strjoin(content, env_value);
		free(content);
		free(env_value);
	}
	else
	{
		content = target_llist->content;
		target_llist->content = ft_strdup(input);
		free(content);
	}
}

bool	add_new_key_value(bool end_in_plus, char *input, char *env_key, t_list *env)
{
	char	*new_key_value;

	if (end_in_plus)
		{
			if (!(new_key_value = join_key_value(env_key, input)))
				return (false);
			ft_lstadd_back(&env, ft_lstnew(new_key_value));
		}
		else
			ft_lstadd_back(&env, ft_lstnew(ft_strdup(input)));
	return (true);
}

bool	check_env_key(char *env_key, bool *end_in_plus, char **key_values)
{
	if (has_plus(env_key))
	{
		*end_in_plus = true;
		env_key[ft_strlen(env_key) - 1] = '\0';
	}
	if (!validate_env_key(env_key))
	{
		free_and_set_error(key_values, env_key);
		free(env_key);
		return (false);
	}
	return (true);
}

bool	update_env(t_list *env, char *env_key, bool end_in_plus, char *input)
{
	t_list	*target_llist;
	bool	ret;

	ret = true;
	if((target_llist = find_env_target_list(env, env_key)))
	{
		if (!update_value(end_in_plus, target_llist, input))
			ret = false;
	}
	else
	{
		if (!add_new_key_value(end_in_plus, input, env_key, env))
			ret = false;
	}
	free(env_key);
	return (ret);
}

// key validation
// 이미 존재하는 키라면 밸류를 덮어쓰기
// 연결하는 문자가 = 가 아니라 += 라면 밸류 뒤에 붙이기
bool	export(t_cmd_line *cmd_line, t_list *env, char* pipe_input)
{
	char	**key_values;
	char	*env_key;
	bool	end_in_plus;
	int		i;
	int		ret;

	ret = true;
	key_values = ft_split(cmd_line->param, ' ');
	i = 0;
	while (key_values[i])
	{
		end_in_plus = false;
		if (*(key_values[i]) == '=')
			return (free_and_set_error(key_values, key_values[i]));
		env_key = get_env_key(key_values[i]);
		if (!(ret = check_env_key(env_key, &end_in_plus, key_values)))
			return (false);
		if (!(update_env(env, env_key, end_in_plus, key_values[i])))
			return (false);
		// if((target_llist = find_env_target_list(env, env_key)))
		// 	update_value(end_in_plus, target_llist, key_values[i]);
		// else
		// 	add_new_key_value(end_in_plus, key_values[i], env_key, env);
		i++;
	}
	free_str_array(key_values);
	return (true);
}



