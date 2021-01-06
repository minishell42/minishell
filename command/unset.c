#include "command.h"

bool	is_valid_key(char *env_key)
{
	int		i;

	i = 0;
	if (ft_isdigit(*env_key))
		return (false);
	while (env_key[i] && env_key[i] != '=')
	{
		if (is_contained(env_key[i], "!@#$%^&*()_+."))
			return (false);
		i++;
	}
	return (true);
}

t_list	*get_valid_param(t_list *param)
{
	t_list *valid_params;

	valid_params = NULL;
	while (param)
	{
		if (is_valid_key(param->content))
		{
			if (valid_params)
				ft_lstadd_back(&valid_params, \
							ft_lstnew(ft_strdup(param->content)));
			else
				valid_params = ft_lstnew(ft_strdup(param->content));
		}
		else
			make_err_msg(EXIT_FAILURE, "unset", param->content,
						get_err_msg(INVALID_EXPORT_PARAM));
		param = param->next;
	}
	return (valid_params);
}

void	check_and_remove_env_value(t_list *param, char *key,
									t_list **env, t_list *prev_env)
{
	while (param)
	{
		if (are_equal(param->content, key))
		{
			prev_env->next = (*env)->next;
			ft_lstdelone(*env, free);
			*env = NULL;
			return ;
		}
		param = param->next;
	}
}

void	search_and_remove_env(t_list *params)
{
	t_list	*env;
	t_list	*prev;
	char	*key;
	int		i;

	env = g_env;
	prev = env;
	while (env)
	{
		i = 0;
		while ((((char *)env->content)[i] != '=') && ((char *)env->content)[i])
			i++;
		key = ft_substr(env->content, 0, i);
		check_and_remove_env_value(params, key, &env, prev);
		free(key);
		if (!env && prev != g_env)
			env = prev->next;
		else
		{
			prev = env;
			env = env->next;
		}
		i++;
	}
}

bool	ft_unset(t_cmd_line *cmd_line)
{
	t_list	*params;

	if (!(params = get_valid_param(cmd_line->param)))
		return (false);
	search_and_remove_env(params);
	ft_lstclear(&params, free);
	if (g_err)
		return (false);
	return (true);
}
