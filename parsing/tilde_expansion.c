#include "parsing.h"

t_list	*env_target_list(char *target)
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

char	**set_path_arr(void)
{
	t_list			*paths;
	char			*value;
	char			**path_arr;

	if (!(paths = env_target_list("PATH")))
		return (NULL);
	value = ft_strchr(paths->content, '=');
	if (!value || !(value + 1))
		return (NULL);
	value++;
	if (!(path_arr = ft_split(value, ':')))
		return (NULL);
	return (path_arr);
}

char	*set_tilde_dir(char *user_name)
{
	char	*tilde_dir;
	char	**path_arr;
	char	*root_path;
	char	*tmp;
	char	*result;

	path_arr = set_path_arr();
	root_path = ft_strdup(path_arr[0]);
	free_str_array(path_arr);
	tmp = ft_strchr(root_path + 1, '/');
	result = ft_substr(root_path, 0, tmp - root_path + 1);
	free(root_path);
	tilde_dir = ft_strjoin(result, user_name);
	free(result);
	return (tilde_dir);
}

int		can_apply_tilde_expansion(char *before_str)
{
	if (*before_str == '~')
	{
		if (!before_str[1])
			return (1);
		else if (before_str[1] == '/')
			return (2);
		else if (before_str[1] == '+')
		{
			if (before_str[2] && before_str[2] != '/')
				return (-1);
			return (3);
		}
		else if (before_str[1] == '-')
		{
			if (before_str[2] && before_str[2] != '/')
				return (-1);
			return (4);
		}
		else if (ft_strchr(before_str, '/'))
			return (5);
	}
	return (-1);
}

char	*apply_tilde_expansion(char *before_str)
{
	int			apply_case;

	if ((apply_case = can_apply_tilde_expansion(before_str)) < 0)
		return (ft_strdup(before_str));
	if (apply_case == 1)
		return (tilde_expansion_dir());
	else if (apply_case == 2)
		return (set_tilde_case2(before_str));
	else if (apply_case == 3)
		return (set_tilde_case3(before_str));
	else if (apply_case == 4)
		return (set_tilde_case4(before_str));
	else if (apply_case == 5)
		return (set_tilde_case5(before_str));
	return (ft_strdup(before_str));
}
