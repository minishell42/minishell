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

	(*i)++; // i = 1;
	env_key = str + *i; // E -> env_key 시작점 env_key = ENV_TEST$123
	while (str[*i] && str[*i] != ' ' && str[*i] != '\\' && str[*i] != '$') // i = 8
		(*i)++;
	seperator = str[*i];	// \0
	str[*i] = 0;			// \0
	env_value = get_env_value(env_key, env); // env_key = ENV_TEST , env -> env_key = 1234
	temp = *ret;	// tmp = ""
	*ret = ft_strjoin(*ret, env_value); // ret = "" + 1234 
	str[*i] = seperator;	// str[8] = sep; i-> ' '
	free(env_value);
	free(temp);
}

char	*set_multi_env(char *str, t_list *env)
{
	// 스트링 안에 들어있는 $로 시작하는 문자열을 모두 환경변수로 대체한다
	// $로 시작하는 문자열이 환경변수로 등록되어 있지 않다면 빈문자열로 대체한다.

	char	*ret;
	char	*temp;
	int		i;
	char	*start;
	char	seperator;

	i = 0;
	ret = ft_calloc(1, sizeof(char));
	start = str;
	printf("param : %s\n", str);
	while (str[i])
	{
		// $ENV_TEST$123
		while (str[i] && str[i] != '$')
			i++;
		seperator = str[i]; // i = 0
		str[i] = 0;  // str[0] = \0 str = ""
		temp = ret; // temp = ""
		ret = ft_strjoin(ret, start); // ret = ""
		free(temp);
		if (seperator == '$')
			join_env_value(&ret, str, &i, env); // ret = "", str = "", i = 0, env -> i
		// if (str[i])
		// 	i++;
		start = str + i;
	}
	return (ret);
}
