/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangpark <sangpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/06 15:14:36 by sangpark          #+#    #+#             */
/*   Updated: 2020/04/14 16:37:53 by sangpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			get_del_count(char const *s, int start_idx, char del)
{
	int		count;
	int		i;

	count = 0;
	i = start_idx;
	while (s[i])
	{
		if (s[i] == del && s[i + 1] != del && s[i + 1] != '\0')
			count++;
		i++;
	}
	return (count);
}

static char			*get_content_ptr(char const *s, int content_len)
{
	char	*content_ptr;
	int		i;

	content_ptr = (char *)ft_calloc((content_len + 1), sizeof(char));
	if (!content_ptr)
		return (0);
	i = 0;
	while (i < content_len)
	{
		content_ptr[i] = s[i];
		i++;
	}
	return (content_ptr);
}

static void			make_copy(char **res, char const *s, int start, char del)
{
	int		empty_res_idx;
	int		content_len;
	int		i;

	empty_res_idx = 0;
	content_len = 0;
	i = start;
	while (s[i])
	{
		if (s[i] == del)
		{
			res[empty_res_idx++] = get_content_ptr(s + start, content_len);
			while (s[i] == del && s[i + 1])
				i++;
			start = i;
			content_len = 0;
		}
		content_len++;
		i++;
	}
	if (s[start] && s[start] != del)
		res[empty_res_idx++] = get_content_ptr(s + start, content_len);
}

static char			**validate(char **res, int delimeter_count)
{
	int		res_count;
	int		i;

	res_count = 0;
	while (res[res_count])
		res_count++;
	i = 0;
	if (res_count != delimeter_count + 1 && res_count > 0)
	{
		while (i < delimeter_count + 1)
		{
			if (res[i])
				free(res[i]);
			i++;
		}
		free(res);
		return (0);
	}
	return (res);
}

char				**ft_split(char const *s, char c)
{
	int		i;
	int		delimeter_count;
	char	**res;

	if (!s || !(*s))
	{
		res = (char **)ft_calloc(1, sizeof(char *));
		if (!res)
			return (0);
		return (res);
	}
	i = 0;
	while (s[i] == c)
		i++;
	delimeter_count = get_del_count(s, i, c);
	res = (char **)ft_calloc((delimeter_count + 2), sizeof(char *));
	if (!res)
		return (0);
	make_copy(res, s, i, c);
	return (validate(res, delimeter_count));
}
