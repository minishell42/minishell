/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command_lines.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: park <park@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 05:45:15 by sangpark          #+#    #+#             */
/*   Updated: 2021/01/05 03:49:52 by park             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static bool	set_command(t_cmd_line *cmd_line, char *line, int *index)
{
	int				len;
	char			*start;
	static int		tmp_index = 0;

	start = line + *index;
	if (!check_character_in_line(line, index, is_seperate_character))
		return (false);
	len = (line + *index) - start;
	if (!parse_command(cmd_line, start, len))
	{
		*index = tmp_index;
		tmp_index = 0;
		return (false);
	}
	while (line[*index] == ' ')
		(*index)++;
	if (line[*index])
		tmp_index = *index;
	else
		tmp_index = 0;
	return (true);
}

static int	set_command_line(t_cmd_line *cmd_line, char *line)
{
	char			*start;
	int				len;
	int				index;
	int				tmp_index;

	index = 0;
	tmp_index = 0;
	while (line[index])
	{
		if (!set_command(cmd_line, line, &index))
		{
			if (g_err)
				return (-1);
			break ;
		}
	}
	start = line + index;
	if ((tmp_index = set_param(cmd_line, start)) < 0)
		return (-1);
	index += tmp_index;
	return (index);
}

t_cmd_line	*get_command_line(char **line_ptr)
{
	t_cmd_line		*command_line;
	int				index;
	char			*line;

	index = 0;
	while (ft_isspace((*line_ptr)[index]) && (*line_ptr)[index])
		index++;
	line = *line_ptr + index;
	if (!(command_line = ft_calloc(sizeof(t_cmd_line), 1)))
		return (NULL);
	index = set_command_line(command_line, line);
	if (index < 0 || !set_redirection_param(command_line))
	{
		free_cmd_struct(command_line);
		return (NULL);
	}
	*line_ptr = line + index;
	return (command_line);
}
