/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_param.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: park <park@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 05:46:05 by sangpark          #+#    #+#             */
/*   Updated: 2021/01/03 06:30:23 by park             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char		*make_valid_value(char *str)
{
	int			i;
	int			start;
	char		*result;
	char		*str_tmp;
	char		*r_tmp;

	i = 0;
	start = i;
	result = ft_calloc(sizeof(char), 1);
	while (str[i])
	{
		str_tmp = convert_to_quote_str(str, start, &i);
		r_tmp = result;
		result = ft_strjoin(r_tmp, str_tmp);
		free(r_tmp);
		if (str[i])
			i++;
		start = i;
		free(str_tmp);
	}
	return (result);
}

char		*convert_to_valid_value(char *start, int len)
{
	char		*result;
	char		*str;
	char		*tmp;

	str = ft_calloc(sizeof(char), len + 1);
	ft_strlcpy(str, start, len + 1);
	result = make_valid_value(str);
	free(str);
	return (result);
}

int			set_param(t_cmd_line *command_line, char *start)
{
	char		*param;
	int			param_len;
	int			i;

	i = 0;
	if (!check_character_in_line(start, &i, is_separator))
		return (-1);
	if (start[i] == '|')
		command_line->pipe_flag = true;
	param = ft_substr(start, 0, i);
	command_line->param = ft_lstnew(param);
	if (start[i])
		i++;
	return (i);
}
