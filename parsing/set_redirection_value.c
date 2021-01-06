/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redirection_value.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dokang <dokang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 05:46:17 by sangpark          #+#    #+#             */
/*   Updated: 2021/01/06 17:53:29 by dokang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static bool	set_param_before_redir(t_cmd_line *cmd_line,
								char *param, int *index)
{
	char	*before_param;

	if (!check_character_in_line(param, index, is_redirection))
		return (false);
	if (!(before_param = ft_substr(param, 0, *index)))
		return (false);
	cmd_line->param = make_param_list(before_param);
	free(before_param);
	return (true);
}

static bool	make_redir_param(t_cmd_line *cmd_line, \
						char *param, int *index, int *start)
{
	char	*redir_content;

	if (param[*index] == '>' && *start + 1 == *index)
	{
		(*index)++;
		check_character_in_line(param, index, is_redirection);
	}
	if (!(redir_content = ft_substr(param, *start, *index - *start)))
		return (false);
	*start = *index;
	if (!can_make_redir_list(cmd_line, redir_content))
	{
		free(redir_content);
		return (false);
	}
	free(redir_content);
	if (param[*index] != '\0')
		(*index)++;
	return (true);
}

bool		check_and_set_redir_param(char *param, int *index,
								t_cmd_line *cmd_line, int start)
{
	while (param[*index] != '\0' &&
		check_character_in_line(param, index, is_redirection))
	{
		if (!make_redir_param(cmd_line, param, index, &start))
			return (false);
	}
	return (true);
}

bool		get_redirection_param(t_cmd_line *cmd_line,
								char *param, int *index)
{
	int		start;

	start = 0;
	if (param[*index])
		start = (*index)++;
	if (!(check_and_set_redir_param(param, index, cmd_line, start)))
		return (false);
	if (g_err)
		return (false);
	return (true);
}

bool		set_redirection_param(t_cmd_line *cmd_line)
{
	char	*param;
	t_list	*param_list;
	int		index;

	param_list = cmd_line->param;
	param = (char *)cmd_line->param->content;
	index = 0;
	if (!set_param_before_redir(cmd_line, param, &index))
		return (false);
	if (!param[index])
	{
		free(param);
		free(param_list);
		return (true);
	}
	if (!get_redirection_param(cmd_line, param, &index))
	{
		free(param);
		free(param_list);
		return (false);
	}
	free(param);
	free(param_list);
	return (true);
}
