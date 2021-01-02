/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: park <park@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 05:46:42 by sangpark          #+#    #+#             */
/*   Updated: 2021/01/03 06:39:25 by park             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int			get_command_num(char *command)
{
	if (are_equal(command, "echo"))
		return (ECHO);
	else if (are_equal(command, "cd"))
		return (CD);
	else if (are_equal(command, "pwd"))
		return (PWD);
	else if (are_equal(command, "export"))
		return (EXPORT);
	else if (are_equal(command, "unset"))
		return (UNSET);
	else if (are_equal(command, "env"))
		return (ENV);
	else if (are_equal(command, "exit"))
		return (EXIT);
	return (0);
}

static bool	parse_cmd(t_cmd_line *cmd_line, char *value)
{
	char	*temp;

	if (temp = change_to_absolute_path(value))
	{
		cmd_line->command = temp;
		cmd_line->command_num = EXCUTABLE;
		free(value);
	}
	else
		cmd_line->command = value;
	if (!cmd_line->command_num)
		cmd_line->command_num = get_command_num(cmd_line->command);
	return (true);
}

bool		parse_command(t_cmd_line *cmd_line, char *start, int len)
{
	char	*value;

	value = convert_to_valid_value(start, len);
	if (!cmd_line->command)
	{
		if (value[0] == '>' || value[0] == '<')
		{
			value[0] = 0;
			cmd_line->command = value;
			return (false);
		}
		return (parse_cmd(cmd_line, value));
	}
	else if (cmd_line->command_num == ECHO && are_equal(value, "-n"))
	{
		if (!cmd_line->option)
			cmd_line->option = value;
		else
			free(value);
		return (true);
	}
	free(value);
	return (false);
}
