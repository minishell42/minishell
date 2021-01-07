/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dokang <dokang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 17:01:06 by dokang            #+#    #+#             */
/*   Updated: 2021/01/07 17:01:09 by dokang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	apply_echo_option(t_cmd_line *cmd_line, char **ret)
{
	char	*tmp;

	if (!cmd_line->option)
	{
		tmp = *ret;
		*ret = (ft_strjoin(*ret, "\n"));
		free(tmp);
	}
}

char	*make_param_str(t_list *param_list)
{
	char	*param;
	char	*tmp;
	char	*result;

	result = ft_calloc(sizeof(char), 1);
	while (param_list)
	{
		param = (char *)param_list->content;
		tmp = result;
		result = ft_strjoin(result, param);
		free(tmp);
		param_list = param_list->next;
		if (param_list)
		{
			tmp = result;
			result = ft_strjoin(result, " ");
			free(tmp);
		}
	}
	return (result);
}

bool	echo(t_cmd_line *cmd_line)
{
	char	*param;

	param = make_param_str(cmd_line->param);
	if (!(param))
		return (false);
	apply_echo_option(cmd_line, &param);
	if (write(1, param, ft_strlen(param)) < 0)
	{
		free(param);
		return (false);
	}
	free(param);
	return (true);
}
