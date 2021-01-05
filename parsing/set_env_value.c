/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dokang <dokang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 05:47:03 by sangpark          #+#    #+#             */
/*   Updated: 2021/01/05 11:31:50 by dokang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char		*get_env_value(char *target_key)
{
	char	*key;
	char	*value;
	int		i;
	t_list	*env;

	env = g_env;
	while (env)
	{
		i = 0;
		while (((char *)env->content)[i] != '=')
			i++;
		key = ft_substr(env->content, 0, i);
		value = ft_substr(env->content, i + 1, ft_strlen(env->content) - i);
		if (are_equal(target_key, key))
		{
			free(key);
			return (value);
		}
		free(key);
		free(value);
		env = env->next;
	}
	return (ft_calloc(sizeof(char), 1));
}

static char	*convert_to_env_value(char *env_key)
{
	char	*after_question;
	char	*env_value;
	char	*exit_code_str;

	if (env_key[0] == '?')
	{
		after_question = env_key + 1;
		exit_code_str = ft_itoa(g_exit_code);
		env_value = ft_strjoin(exit_code_str, after_question);
		free(exit_code_str);
		return (env_value);
	}
	return (get_env_value(env_key));
}

static void	join_env_value(char **ret, char *str, int *i)
{
	char	*env_key;
	char	*env_value;
	char	*temp;
	char	seperator;

	(*i)++;
	env_key = str + *i;
	while (str[*i] && str[*i] != ' ' && str[*i] != '\\'
			&& str[*i] != '$' && str[*i] != '\'')
		(*i)++;
	seperator = str[*i];
	str[*i] = 0;
	env_value = convert_to_env_value(env_key);
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
	// back 슬래시 flag on , off
	// on 조건
	// back 슬래시가 존재할때
	// back 슬래시는 무시된다.
	// off 조건
	// 문자가 존재 할때
	// 특정 문자를 제외하고 백슬래시를 앞에 추가해 준다.
	// echo "\$test"
	printf("before str = %s\n", str);
	// bool b_flag;
// echo "h\a\$test \"$test"
// echo "h\a\$test \'$test"
	// b_flag = false;
	printf("===============  start loop  =====================\n");
	while (str[i])
	{
		// \$test
		printf("str = %s\n", ret);
		while (str[i] && str[i] != '$' && str[i] != '\\')
		{
			// if (str[i] == '\\')
			// {
			// 	i++;
			// 	if (str[i] == '\'' || str[i] == '"' || str[i] == '\\' || str[i] == '$')
			// 		start++;
			// }
			i++;
		}
		// str[i] == '\\'	str[i] == '$'

		seperator = str[i];
		str[i] = 0;
		temp = ret;
		ret = ft_strjoin(temp, start);  //ret : '\\' 
		free(temp);
		if (seperator == '$')
			join_env_value(&ret, str, &i);
		start = str + i;
	}
	printf("===============  end loop  =====================\n");
	return (ret);
}
