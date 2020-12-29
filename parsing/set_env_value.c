#include "parsing.h"

char 		*get_env_value(char *target_key)
{
	char	*key;
	char	*value;
	int		i;
	t_list	*env_list;

	env_list = g_env;
	while (env_list)
	{
		i = 0;
		while (((char *)env_list->content)[i] != '=')
			i++;
		key = ft_substr(env_list->content, 0, i);
		value = ft_substr(env_list->content, i + 1, ft_strlen(env_list->content) - i);
		if (are_equal(target_key, key))
		{
			free(key);
			return (value);
		}
		free(key);
		free(value);
		env_list = env_list->next;
	}
	return (ft_calloc(sizeof(char), 1));
}

static char	*get_absolute_path(char *value, int index)
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
		tmp = get_env_value("HOME");
	return (tmp);
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
	if ((tmp = get_absolute_path(value, i)))
	{
		result = ft_strjoin(tmp, value + i);
		free(tmp);
	}
	return (result);
}

void 		join_env_value(char **ret, char *str, int *i)
{
	char	*env_key;
	char	*env_value;
	char	*temp;
	char	seperator;

	(*i)++;
	env_key = str + *i;
	// printf("what is env_key before ? '%s'\n", env_key);
	while (str[*i] && str[*i] != ' ' && str[*i] != '\\' && str[*i] != '$' && str[*i] != '\'')
		(*i)++;
	seperator = str[*i];
	str[*i] = 0;
	// printf("what is env_key after ? '%s'\n", env_key);
	env_value = get_env_value(env_key);
	// printf("what is env_value ? '%s'\n", env_value);
	temp = *ret;
	*ret = ft_strjoin(temp, env_value);
	str[*i] = seperator;
	free(env_value);
	free(temp);
}

char		*set_multi_env(char *str)
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
		// printf("what is start before? '%s'\n", start);
		ret = ft_strjoin(temp, start);
		// printf("what is ret before? '%s'\n", ret);
		free(temp);
		if (seperator == '$')
			join_env_value(&ret, str, &i);
		// printf("what is ret after? '%s'\n", ret);
		start = str + i;
		// printf("what is start after? '%s'\n", start);
	}
	return (ret);
}

// char		*set_multi_env(char *str, t_list *env)
// {
// 	char	*ret;
// 	char	*temp;
// 	int		i;
// 	char	*start;
// 	char	seperator;

// 	i = 0;
// 	ret = ft_calloc(1, sizeof(char));
// 	start = str;
// 	while (str[i])
// 	{
// 		while (str[i] && str[i] != '$')
// 			i++;
// 		seperator = str[i];
// 		str[i] = 0;
// 		temp = ret;
// 		printf("what is start before? '%s'\n", start);
// 		ret = ft_strjoin(temp, start);
// 		printf("what is ret before? '%s'\n", ret);
// 		free(temp);
// 		if (seperator == '$')
// 			join_env_value(&ret, str, &i, env);
// 		printf("what is ret after? '%s'\n", ret);
// 		start = str + i;
// 		printf("what is start after? '%s'\n", start);
// 	}
// 	return (ret);
// }
