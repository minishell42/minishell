/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dokang <dokang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 17:01:28 by dokang            #+#    #+#             */
/*   Updated: 2021/01/07 17:01:30 by dokang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

void	print_content(void *content)
{
	int			len;
	char		*str;

	if (!content)
		return ;
	str = content;
	len = ft_strlen(content);
	str[len] = '\n';
	write(1, str, len + 1);
	str[len] = '\0';
}

bool	run_command_in_env(t_list *param)
{
	char		*param_str;
	char		*tmp;
	t_cmd_line	*env_cmd_line;

	param_str = make_param_str(param);
	tmp = param_str;
	if (!(env_cmd_line = get_command_line(&param_str)))
	{
		free(tmp);
		return (false);
	}
	if (!run_command(env_cmd_line))
	{
		free_cmd_struct(env_cmd_line);
		free(tmp);
		return (false);
	}
	free_cmd_struct(env_cmd_line);
	free(tmp);
	return (true);
}

bool	ft_env(t_cmd_line *cmd_line)
{
	t_list		*param;

	param = cmd_line->param;
	while (param)
	{
		if (ft_strchr(param->content, '='))
			ft_lstadd_back(&g_env, ft_lstnew(ft_strdup(param->content)));
		else
			break ;
		param = param->next;
	}
	if (param)
	{
		if (!(run_command_in_env(param)))
			return (false);
	}
	else
		ft_lstiter(g_env, print_content);
	return (true);
}
