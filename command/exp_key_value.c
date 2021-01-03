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
		make_err_msg(EXIT_FAILURE, cmd_line->command, key_value,
					get_err_msg(INVALID_EXPORT_PARAM));
		return (false);
	}
	return (true);
}

t_list	*find_env_target_list(char *target)
{
	char	*key;
	char	*value;
	int		i;
	t_list	*env;

	env = g_env;
	while (env)
	{
		i = 0;
		while ((((char *)env->content)[i] != '=') && ((char *)env->content)[i])
			i++;
		key = ft_substr(env->content, 0, i);
		value = ft_substr(env->content, i + 1, ft_strlen(env->content) - i);
		if (are_equal(target, key))
		{
			free(key);
			free(value);
			return (env);
		}
		free(key);
		free(value);
		env = env->next;
	}
	return (NULL);
}

void	set_env_target(char *target, char *value)
{
	t_list	*target_env;
	char	*target_tmp;
	void	*tmp;

	if (!(target_env = find_env_target_list(target)))
	{
		target_env = ft_calloc(sizeof(t_list), 1);
		target_tmp = ft_strjoin(target, "=");
		target_env->content = ft_strjoin(target_tmp, value);
		free(target_tmp);
		target_env->next = NULL;
		ft_lstadd_back(&g_env, target_env);
	}
	else
	{
		tmp = target_env->content;
		target_tmp = ft_strjoin(target, "=");
		target_env->content = ft_strjoin(target_tmp, value);
		free(target_tmp);
		free(tmp);
	}
}
