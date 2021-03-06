/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_character.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dokang <dokang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 17:20:54 by dokang            #+#    #+#             */
/*   Updated: 2021/01/07 17:20:56 by dokang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int			is_separator(int c)
{
	if (c == ';' || c == '|')
		return (true);
	return (false);
}

int			is_redirection(int c)
{
	if (c == '<' || c == '>')
		return (true);
	return (false);
}

int			is_semicolon(int c)
{
	if (c == ';')
	{
		return (true);
	}
	return (false);
}

int			is_delimitor(int c)
{
	if (is_separator(c) || is_redirection(c) || is_semicolon(c))
		return (true);
	return (false);
}

bool		is_empty_line(char *line)
{
	int		i;

	if (!line)
		return (true);
	i = 0;
	while (ft_isspace(line[i]))
		i++;
	if ((line[i] == '\n' && !line[i + 1]) || !line[i])
		return (true);
	return (false);
}
