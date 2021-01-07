/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dokang <dokang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 17:03:56 by dokang            #+#    #+#             */
/*   Updated: 2021/01/07 17:03:58 by dokang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

bool		update_value(t_list *target_llist, t_export *exp_info)
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

bool		add_new_key_value(t_export *exp_info)
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

bool		update_env(t_export *exp_info)
{
	t_list	*target_llist;

	if (!exp_info->has_separator)
		return (true);
	if ((target_llist = find_env_target_list(exp_info->env_key)))
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

t_export	*init_export(t_cmd_line *cmd_line, \
						char **key_values, char *key_value)
{
	t_export	*exp_info;

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

bool		export(t_cmd_line *cmd_line)
{
	t_export	*exp_info;
	char		**key_values;
	int			ret;
	int			i;

	if (!cmd_line->param)
		ft_lstiter(g_env, print_content_exp);
	if (cmd_line->pipe_flag)
		return (true);
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
