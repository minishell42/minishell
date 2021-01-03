/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_to_absolute_path.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangpark <sangpark@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 04:43:34 by sangpark          #+#    #+#             */
/*   Updated: 2021/01/04 04:43:36 by sangpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static char	*get_absolute_path(char *value, int index)
{
	char	*tmp;
	int		curr_len;

	curr_len = 0;
	tmp = NULL;
	if (index != 0 && value[index - 1] == '.')
	{
		tmp = getcwd(NULL, 0);
		if (index != 1 && value[index - 2] == '.')
		{
			curr_len = ft_strlen(tmp) - 1;
			while (curr_len >= 0 && tmp[curr_len] != '/')
			{
				tmp[curr_len] = '\0';
				curr_len--;
			}
			if (tmp[curr_len] == '/')
				tmp[curr_len] = '\0';
		}
	}
	else if (index != 0 && value[index - 1] == '~')
		tmp = get_env_value("HOME");
	return (tmp);
}

char		*change_to_absolute_path(char *value)
{
	char	*result;
	char	*tmp;
	int		i;
	int		curr_len;

	tmp = NULL;
	result = NULL;
	i = 0;
	while (value[i] && value[i] != '/')
		i++;
	if (!value[i])
	{
		if ((!are_equal(value, ".") && !are_equal(value, "..")))
			return (0);
	}
	if ((tmp = get_absolute_path(value, i)))
	{
		result = ft_strjoin(tmp, value + i);
		free(tmp);
	}
	return (result);
}
