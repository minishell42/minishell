#include "parsing.h"

char 		*get_env_value(char *target_key, t_list *env)
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

static char	*get_absolute_path(char *value, t_list *env, int index)
{
	char	*tmp;
	int		curr_len;

	curr_len = 0;
	tmp = NULL;
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
	}
	else if (index != 0 && value[index - 1] == '~')
		tmp = get_env_value("HOME", env);
	return (tmp);
}

char		*change_to_absolute_path(char *value, t_list *env)
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
	if ((tmp = get_absolute_path(value, env, i)))
	{
		result = ft_strjoin(tmp, value + i);
		free(tmp);
	}
	// if (i != 0 && value[i - 1] == '.')
	// {
	// 	tmp = getcwd(NULL, 0);
	// 	if (i != 1 && value[i - 2] == '.')
	// 	{
	// 		curr_len = ft_strlen(tmp) - 1;
	// 		while (curr_len >= 0 && tmp[curr_len] != '/')
	// 		{
	// 			tmp[curr_len] = '\0';
	// 			curr_len--;
	// 		}
	// 		if (tmp[curr_len] == '/')
	// 			tmp[curr_len] = '\0';
	// 	}
	// }
	// else if (i != 0 && value[i - 1] == '~')
	// 	tmp = get_env_value("HOME", env);
	// if (tmp != NULL)
	// 	result = ft_strjoin(tmp, value + i);
	return (result);
}

void 		join_env_value(char **ret, char *str, int *i, t_list *env)
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

char		*set_multi_env(char *str, t_list *env)
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
