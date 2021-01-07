/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dokang <dokang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 17:21:10 by dokang            #+#    #+#             */
/*   Updated: 2021/01/07 17:21:11 by dokang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void		remove_quotation(char *value)
{
	char		quot_flag;
	int			index;

	quot_flag = 0;
	while (value && *value)
	{
		index = 0;
		while (*value && *value != '"' && *value != '\'')
			value++;
		if (*value == '"' || *value == '\'')
		{
			if (quot_flag == 0)
				quot_flag = *value;
			else if (quot_flag == *value)
				quot_flag = 0;
		}
		if (quot_flag == *value || quot_flag == 0)
			while (value && value[index++])
				value[index - 1] = value[index];
		else
			value++;
	}
}

void		free_str_array(char **strs)
{
	int			i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

bool		is_contained(char c, char *str)
{
	int			i;

	i = 0;
	while (str[i])
	{
		if (c == str[i])
		{
			return (true);
		}
		i++;
	}
	return (0);
}

int			is_seperate_character(int c)
{
	if (ft_isspace(c) || is_redirection(c))
		return (true);
	return (false);
}

char		*ft_join_strs(char **strs)
{
	char	*res;
	int		res_len;
	int		i;

	if (!strs)
		return (NULL);
	i = 0;
	res_len = 0;
	while (strs[i])
		res_len += ft_strlen(strs[i++]);
	if (!(res = ft_calloc(sizeof(char), res_len + 1)))
		return (NULL);
	i = 0;
	while (strs[i])
	{
		ft_strlcat(res, strs[i], res_len + 1);
		i++;
	}
	return (res);
}
