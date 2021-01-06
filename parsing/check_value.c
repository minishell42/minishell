/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_value.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: park <park@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 05:45:44 by sangpark          #+#    #+#             */
/*   Updated: 2021/01/05 03:24:23 by park             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool			pass_escape(char *line, int *index, char quot_flag)
{
	if (line[*index] == '\\')
	{
		(*index)++;
		if (!line[*index])
		{
			make_err_msg(SYNTAX_ERROR, 0, "\\", \
							get_err_msg(SYNTAX_ERROR));
			return (false);
		}
		if (line[*index] == '\"')
			(*index)++;
	}
	return (true);
}

bool			check_character_in_line(char *line,
					int *index, int (*func)())
{
	char	quot_flag;

	quot_flag = 0;
	while (line[*index] && !(func(line[*index]) && quot_flag == 0))
	{
		if (!(pass_escape(line, index, quot_flag)))
			return (false);
		if (line[*index] == '\'' || line[*index] == '"')
		{
			if (quot_flag == line[*index])
				quot_flag = 0;
			else if (quot_flag == 0)
				quot_flag = line[*index];
		}
		(*index)++;
	}
	if (quot_flag)
	{
		set_quot_err(quot_flag);
		return (false);
	}
	return (true);
}

bool			check_cmd_num(t_cmd_line *cmd_line)
{
	t_list	*redir;

	redir = cmd_line->redir_param;
	if (!cmd_line->command_num)
	{
		if (!redir || *cmd_line->command)
		{
			make_err_msg(INVALID_COMMAND, 0,
						cmd_line->command, get_err_msg(INVALID_COMMAND));
			return (false);
		}
	}
	return (true);
}
