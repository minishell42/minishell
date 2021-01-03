/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redirection_value.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: park <park@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 05:46:17 by sangpark          #+#    #+#             */
/*   Updated: 2021/01/04 03:34:11 by park             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	set_param_before_redir(t_cmd_line *cmd_line,
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

bool	check_and_set_redir_param(char *param, int *index,
								t_cmd_line *cmd_line, int start)
{
	char	*redir_content;

	while (param[*index] != '\0' &&
		check_character_in_line(param, index, is_redirection))
	{
		if (param[*index] == '>' && start + 1 == *index)
		{
			(*index)++;
			check_character_in_line(param, index, is_redirection);
		}
		if (!(redir_content = ft_substr(param, start, *index - start)))
			return (false);
		start = *index;
		if (!can_make_redir_list(cmd_line, param, redir_content))
		{
			free(redir_content);
			return (false);
		}
		free(redir_content);
		if (param[*index] != '\0')
			(*index)++;
	}
	return (true);
}

bool	get_redirection_param(t_cmd_line *cmd_line,
								char *param, int *index)
{
	int		start;

	if (param[*index])
		start = (*index)++;
	if (!(check_and_set_redir_param(param, index, cmd_line, start)))
		return (false);
	if (g_err)
		return (false);
	return (true);
}

bool	set_redirection_param(t_cmd_line *cmd_line)
{
	char	*param;
	t_list	*param_list;
	char	*tmp;
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
