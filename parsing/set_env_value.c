#include "parsing.h"

char *get_env_value(char *target_key, t_list *env)
{
	char	*key;
	char	*value;
	char	**key_value;

	while (env)
	{
		key_value = ft_split((char *)env->content, '=');
		key = key_value[0];
		value = key_value[1];
		if (are_equal(target_key, key))
		{
			free(key);
			free(key_value);
			return (value);
		}
		env = env->next;
	}
	free(key);
	free(key_value);
	value[0] = 0;
	return (value);
}

void join_env_value(char **ret, char *str, int *i, t_list *env)
{
	char	*env_key;
	char	*env_value;
	char	*temp;
	char	seperator;

	(*i)++;
	env_key = str + *i;
	while (str[*i] && str[*i] != ' ' && str[*i] != '\\' && str[*i] != '$')
		(*i)++;
	seperator = str[*i];
	str[*i] = 0;
	env_value = get_env_value(env_key, env);
	temp = *ret;
	*ret = ft_strjoin(*ret, env_value);
	str[*i] = seperator;
	free(env_value);
	free(temp);
}

char	*set_multi_env(char *str, t_list *env)
{
	char	*ret;
	char	*temp;
	int		i;
	char	*start;
	char	seperator;

	i = 0;
	ret = ft_calloc(1, sizeof(char));
	start = str;
	while (str[i])
	{
		while (str[i] && str[i] != '$')
			i++;
		seperator = str[i];
		str[i] = 0;
		temp = ret;
		ret = ft_strjoin(ret, start);
		free(temp);
		if (seperator == '$')
			join_env_value(&ret, str, &i, env);
		start = str + i;
	}
	return (ret);
}
